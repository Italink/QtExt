#include "QObjectEx.h"
#include <QMetaObject>
#include <QJsonArray>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QDataStream>
#include "QFile"

QObjectPanel* QObjectEx::createQObjectPanel(QObject* object){
	return new QObjectPanel(object);
}

static QJsonObject metaObjectToJson(const QMetaObject* meta, QObject* object) {
	QJsonObject ObjectInfo;
	ObjectInfo["ClassName"] = meta->className();

	QJsonObject properties;
	for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++) {
		QMetaProperty property = meta->property(i);
		QJsonObject propInfo;
		propInfo["Type"] = property.typeName();
		QByteArray data;
		QDataStream stream(&data,QFile::WriteOnly);
		stream<<property.read(object);
		propInfo["Data"] = QString::fromLatin1(data);
		properties[property.name()] = propInfo;
	}
	if (!properties.isEmpty()) {
		ObjectInfo["Properties"] = properties;
	}

	if (meta->superClass() != nullptr) {
		ObjectInfo["SuperClass"] = metaObjectToJson(meta->superClass(),object);
	}
	return ObjectInfo;
}

QJsonObject QObjectEx::toJson(QObject* object){
	QJsonObject json;
	const QMetaObject* meta = object->metaObject();
	if (meta) {
		return metaObjectToJson(meta,object);
	}
	return QJsonObject();
}

QObject* QObjectEx::fromJson(QJsonObject json)
{
	return nullptr;
}

QByteArray QObjectEx::dump(QObject* object)
{
	QJsonDocument doc(toJson(object));
	return 	(doc.toJson());
}

QByteArray QObjectEx::toByteArray(QObject* object)
{
	return QByteArray();
}

QObject* QObjectEx::fromByteArray(QByteArray byteArray)
{
	return nullptr;
}

