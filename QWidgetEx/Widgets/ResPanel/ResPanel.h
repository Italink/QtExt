#ifndef ResPanel_h__
#define ResPanel_h__

#include <QWidget>
#include "ResListWidget.h"
#include "ResSingleItem.h"

class ResGroupItem;
class ResSingleItem;
class ResModel;

class ResPanel :public QWidget {
	Q_OBJECT
public:
	ResPanel(ResModel* defaultModel);
	ResModel* getManagement() { return resManagement_; };
private:
	void reset();
	void setTopCurrent(QString id);
	void setCurrentSingleItem(QString id);
private:
	ResListWidget topWidget_;
	ResListWidget bottomWidget_;
	QString currentGroupId_;
	QString currentSingleId_;
	ResModel* resManagement_;
Q_SIGNALS:
	void currentSingleItemChanged(ResSingleItem *item);
};

#endif // ResPanel_h__
