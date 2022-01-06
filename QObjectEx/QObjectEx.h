#include "QObjectPanel/QObjectPanel.h"
#include <QVariant>

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

class QObjectEx : public QObject {
public:
	virtual QObjectPanel* createQObjectPanel();
	virtual QString dump();
	virtual QByteArray serialize();
	virtual void unserialize(QByteArray byteArray);
	static QObjectEx* createFromData(QByteArray byteArray);
};
