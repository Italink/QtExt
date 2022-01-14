#ifndef ResPanel_h__
#define ResPanel_h__

#include <QWidget>
#include "ResListWidget.h"
#include "ResSingleItem.h"

class ResGroupItem;
class ResManagement;

class ResPanel :public QWidget {
public:
	ResPanel();
private:
	void reset();
private:
	ResListWidget topWidget_;
	ResListWidget bottomWidget_;
	ResGroupItem* currentGroupItem_;
	QString currentCroupId_;
	ResManagement* resManagement_;
};

#endif // ResPanel_h__
