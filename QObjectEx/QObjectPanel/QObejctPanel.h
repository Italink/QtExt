#ifndef QObejctPanel_h__
#define QObejctPanel_h__

#include <QTreeWidget>

class QObjectPanel :public QTreeWidget{
	Q_OBJECT
public:
	QObjectPanel(QObject* object = nullptr);

	QObject* getObject() const;
	void setObject(QObject* val);

Q_SIGNALS:
	void objectChanged(QObject*);

private:
	void updatePanel();

private:
	QObject* object_ = nullptr;
};

#endif // QObejctPanel_h__
