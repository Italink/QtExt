#ifndef QPropertyPanel_h__
#define QPropertyPanel_h__

#include <QTreeWidget>
#include "QObjectEx\QObjectEx.h"

class QPropertyPanel :public QTreeWidget {
public:
	QPropertyPanel(QObjectEx* object = nullptr);
	QObjectEx* getObject() const;
	void setObject(QObjectEx* val);
private:
	void updatePanel();
private:
	QObjectEx* object_ = nullptr;
};

#endif // QPropertyPanel_h__
