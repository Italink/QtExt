#include "QObjectPanel\QObejctPanel.h"

#define Q_AUTO(type,name)\
    Q_PROPERTY(type name READ get_##name WRITE set_##name NOTIFY name##Changed) \
    type& get_##name() { return name; } \
    void set_##name(type var){ \
        if(name==var) \
            return; \
        name = var;  \
        emit name##Changed(QVariant::fromValue(var)); \
    } \
    Q_SIGNAL void name##Changed(QVariant); \
    type name

#define Q_OBJECT_EX \
    Q_OBJECT \
    public: \
        QByteArray serialize() { return QObjectEx::serialize(this);} \
        void unserialize(QByteArray data) { QObjectEx::unserialize(data, this); } \
        QString dump() { return QObjectEx::dump(this); } \
        QObjectPanel* createQObjectPane (){ return QObjectEx::createQObjectPanel(this); } \
    private:

namespace QObjectEx {
QObjectPanel* createQObjectPanel(QObject* object);
QString dump(QObject* object);
QByteArray serialize(QObject* object);
void unserialize(QByteArray byteArray, QObject* object);
}