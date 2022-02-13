#ifndef FlowPanel_h__
#define FlowPanel_h__
#include "QListWidget"

class FlowPanel :public QListWidget{
public:
	FlowPanel();
	void addItem(QString text,QIcon icon);
	QListWidgetItem* getItem(QString name);
};


#endif // FlowPanel_h__
