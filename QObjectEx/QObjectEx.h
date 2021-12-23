#include "QObjectPanel\QObejctPanel.h"

#define Q_AUTO(type,name)\
    Q_PROPERTY(type name READ get_##name WRITE set_##name NOTIFY name##Changed) \
    type get_##name(){ return name; } \
    void set_##name(type var){ \
        if(name==var) \
            return; \
        name = var;  \
        emit name##Changed(QVariant::fromValue(var)); \
    } \
    Q_SIGNAL void name##Changed(QVariant); \
    type name

namespace QObjectEx {
QObjectPanel* createQObjectPanel(QObject* object);
QString dump(QObject* object);
QByteArray serialize(QObject* object);
bool unserialize(QByteArray byteArray, QObject* object);
}