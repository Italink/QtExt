#ifndef QObjectEx_h__
#define QObjectEx_h__

#include "QObjectPanel/QObjectPanel.h"
#include <QVariant>
#include <QUndoStack>
#include "sol/state.hpp"

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

struct propertyInfo {
	QString type;
	QString name;
};

class QObjectEx : public QObject {
	Q_OBJECT
public:
	QObjectEx();
	virtual QObjectPanel* createQObjectPanel();
	virtual void dump();
	virtual QByteArray serialize();
	virtual void unserialize(QByteArray byteArray);
	static QObjectEx* createFromData(QByteArray byteArray);
	static QUndoStack undoStack_;
public:
	Q_AUTO(QString, luaCode_);
};

#endif // QObjectEx_h__
