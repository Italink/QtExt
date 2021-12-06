#include "QObjectPanel\QObejctPanel.h"
#include <QJsonObject>

#define IK_AUTO(type,name)\
    Q_PROPERTY(type name READ get_##name WRITE set_##name NOTIFY name##Changed) \
    type get_##name(){ return name; } \
    void set_##name(type var){ \
        if(name==var) \
            return; \
        name = var;  \
        emit name##Changed(var); \
    } \
    Q_SIGNAL void name##Changed(type); \
    type name


namespace QObjectEx {
	QObjectPanel* createQObjectPanel(QObject *object);
	QJsonObject toJson(QObject * object);
	QObject* fromJson(QJsonObject json);
	QByteArray  dump(QObject *object);
	QByteArray toByteArray(QObject * object);
	QObject* fromByteArray(QByteArray byteArray);
}