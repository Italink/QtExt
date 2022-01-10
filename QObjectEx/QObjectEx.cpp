#include "QObjectEx.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QDataStream>
#include <QCborStreamReader>
#include <QCborStreamWriter>
#include <QCborMap>
#include "QFile"
#include "QMetaType"

QObjectEx::QObjectEx()
{
}

QObjectPanel* QObjectEx::createQObjectPanel() {
	return new QObjectPanel(this);
}

void QObjectEx::dump()
{
	QCborValue cbor = QCborValue::fromCbor(serialize());
	qDebug() << cbor.toDiagnosticNotation(QCborValue::DiagnosticNotationOption::LineWrapped);
}

void serializeInternal(QObject* object, QCborStreamWriter& writer) {
	if (object == nullptr)
		return;
	const QMetaObject* meta = object->metaObject();
	if (meta) {
		writer.startMap(3);
		writer.append(QLatin1String("ClassName"));
		writer.append(QLatin1String(meta->className()));
		writer.append(QLatin1String("Properties"));
		writer.startMap(meta->propertyCount());
		for (int i = 0; i < meta->propertyCount(); i++) {
			QMetaProperty property = meta->property(i);
			writer.append(QLatin1String(property.name()));
			const QMetaObject* meta = property.metaType().metaObject();
			if (meta != nullptr) {
				if (meta->inherits(&QObject::staticMetaObject)) {
					QObject* obj = property.read(object).value<QObject*>();
					if (obj != nullptr) {
						serializeInternal(obj, writer);
						continue;
					}
				}
			}
			QByteArray data;
			QDataStream stream(&data, QFile::WriteOnly);
			stream << property.read(object);
			writer.append(data);
		}
		writer.endMap();

		writer.append(QLatin1String("DynamicProperties"));
		QList<QByteArray> dpNames = object->dynamicPropertyNames();
		writer.startMap(dpNames.size());
		for (auto& dpName : dpNames) {
			writer.append(QLatin1String(dpName));
			QVariant var = object->property(dpName);
			const QMetaObject* meta = var.metaType().metaObject();
			if (meta != nullptr) {
				if (meta->inherits(&QObject::staticMetaObject)) {
					QObject* obj = var.value<QObject*>();
					if (obj != nullptr) {
						serializeInternal(obj, writer);
						continue;
					}
				}
			}
			QByteArray data;
			QDataStream stream(&data, QFile::WriteOnly);
			stream << var;
			writer.append(data);
		}
		writer.endMap();

		writer.endMap();
	}
}

QByteArray QObjectEx::serialize()
{
	QByteArray data;
	QCborStreamWriter writer(&data);
	serializeInternal(this, writer);
	return data;
}

void unserializeInternal(QObject* object, QCborMap cbor)
{
	if (cbor.value("ClassName") == object->metaObject()->className()) {
		QCborMap properties = cbor.value("Properties").toMap();
		for (auto prop : properties.keys()) {
			QVariant var = object->property(prop.toString().toLocal8Bit());
			QObject* obj = var.value<QObject*>();
			if (obj != nullptr && properties[prop].isMap()) {
				QCborMap childCbor = properties[prop].toMap();
				unserializeInternal(obj, childCbor);
				continue;
			}
			QByteArray data = properties[prop].toByteArray();
			QDataStream stream(&data, QFile::ReadOnly);
			stream >> var;
			object->setProperty(prop.toString().toLocal8Bit(), var);
		}
		QCborMap dproperties = cbor.value("DynamicProperties").toMap();
		for (auto prop : dproperties.keys()) {
			QString s = prop.toString();
			QVariant var = object->property(prop.toString().toLocal8Bit());

			QObject* obj = var.value<QObject*>();
			if (obj != nullptr && dproperties[prop].isMap()) {
				QCborMap childCbor = dproperties[prop].toMap();
				unserializeInternal(obj, childCbor);
				continue;
			}
			QByteArray data = dproperties[prop].toByteArray();
			QDataStream stream(&data, QFile::ReadOnly);
			stream >> var;
			object->setProperty(prop.toString().toLocal8Bit(), var);
		}
	}
}

void QObjectEx::unserialize(QByteArray byteArray)
{
	QCborMap cbor = QCborValue::fromCbor(byteArray).toMap();
	unserializeInternal(this, cbor);
}

QObjectEx* QObjectEx::createFromData(QByteArray byteArray)
{
	QCborMap cbor = QCborValue::fromCbor(byteArray).toMap();
	int typeId = QMetaType::type(cbor.value("ClassName").toString().toLatin1());
	QObjectEx* obj = static_cast<QObjectEx*>(QMetaType::create(typeId));
	if (obj) {
		unserializeInternal(obj, cbor);
	}
	return obj;
}

QUndoStack QObjectEx::undoStack_;