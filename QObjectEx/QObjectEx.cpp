#include "QObjectEx.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QDataStream>
#include <QCborStreamReader>
#include <QCborStreamWriter>
#include <QCborMap>
#include "QFile"

QObjectPanel* QObjectEx::createQObjectPanel(QObject* object) {
	return new QObjectPanel(object);
}

QString QObjectEx::dump(QObject* object)
{
	QCborValue cbor = QCborValue::fromCbor(serialize(object));
	return cbor.toDiagnosticNotation(QCborValue::DiagnosticNotationOption::LineWrapped);
}

void serializeInternal(QObject* object, QCborStreamWriter& writer) {
	const QMetaObject* meta = object->metaObject();
	if (meta) {
		writer.startMap(2);
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
		writer.endMap();
	}
}

QByteArray QObjectEx::serialize(QObject* object)
{
	QByteArray data;
	QCborStreamWriter writer(&data);
	serializeInternal(object, writer);
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
	}
}

void QObjectEx::unserialize(QByteArray byteArray, QObject* object)
{
	QCborMap cbor = QCborValue::fromCbor(byteArray).toMap();
	unserializeInternal(object, cbor);
}