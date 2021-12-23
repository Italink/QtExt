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
	return cbor.toDiagnosticNotation();
}

QByteArray QObjectEx::serialize(QObject* object)
{
	QByteArray data;
	QCborStreamWriter writer(&data);
	const QMetaObject* meta = object->metaObject();
	if (meta) {
		writer.startMap(2);
		writer.append(QLatin1String("ClassName"));
		writer.append(QLatin1String(meta->className()));

		writer.append(QLatin1String("Properties"));
		writer.startMap(meta->propertyCount());
		for (int i = 0; i < meta->propertyCount(); i++) {
			QMetaProperty property = meta->property(i);
			QByteArray data;
			QDataStream stream(&data, QFile::WriteOnly);
			stream << property.read(object);
			writer.append(QLatin1String(property.name()));
			writer.append(data);
		}
		writer.endMap();
		writer.endMap();
	}
	return data;
}

bool QObjectEx::unserialize(QByteArray byteArray, QObject* object)
{
	QCborMap cbor = QCborValue::fromCbor(byteArray).toMap();
	if (cbor.value("ClassName") == object->metaObject()->className()) {
		QCborMap properties = cbor.value("Properties").toMap();
		for (auto prop : properties.keys()) {
			QVariant var = object->property(prop.toString().toLocal8Bit());
			QByteArray data = properties[prop].toByteArray();
			QDataStream stream(&data, QFile::ReadOnly);
			stream >> var;
			object->setProperty(prop.toString().toLocal8Bit(), var);
		}
	}
	return true;
}