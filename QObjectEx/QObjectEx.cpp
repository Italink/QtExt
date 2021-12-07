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

static QJsonObject createJson(const QMetaObject* meta, QObject* object) {
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
		propInfo["Data"] = data.toBase64().data();
		properties[property.name()] = propInfo;
	}
	if (!properties.isEmpty()) {
		ObjectInfo["Properties"] = properties;
	}

	if (meta->superClass() != nullptr) {
		ObjectInfo["SuperClass"] = createJson(meta->superClass(),object);
	}
	return ObjectInfo;
}



QJsonObject QObjectEx::toJson(QObject* object){
	QJsonObject json;
	const QMetaObject* meta = object->metaObject();
	if (meta) {
		return createJson(meta,object);
	}
	return QJsonObject();
}

void QObjectEx::fromJson(QJsonObject info, QObject* object)
{
	if (info["ClassName"].toString() != object->metaObject()->className()) {
		return;
	}
	QJsonObject properties = info["Properties"].toObject();
	for (auto& key : properties.keys()) {
		QVariant var = object->property(key.toLocal8Bit().data());
		QByteArray data = QByteArray::fromBase64(properties[key].toObject()["Data"].toString().toLocal8Bit());
		QDataStream stream(&data, QFile::ReadOnly);
		stream >> var;
		object->setProperty(key.toLocal8Bit().data(), var);
	}
	if (info.contains("SuperClass")) {
		fromJson(info["SuperClass"].toObject(), object);
	}
}

QObject* QObjectEx::createFromJson(QJsonObject json)
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

