#ifndef ResManagement_h__
#define ResManagement_h__

#include "QObject"
#include "ResItem.h"
#include "QMap"

class ResSingleItem;

class ResManagement :public QObject {
	Q_OBJECT
public:
	ResManagement();
	bool isGroup(QString id);
	void addNewSingleItem();
	void addResItem(int index, ResItem* item);
	void removeItems(QStringList idList);
	void makeGroup(QStringList idList);
	void takeApart(QString groupId);
	void moveItem(int start, int end, int dst);
	void moveGroupChildItem(QString groupId, int start, int end, int dst);
	void enterGroup(QString groupId, QStringList idList,int dstIndex);
	void leaveGroup(QString groupId, QStringList idList,int dstIndex);
	QStringList getIdList();
	QStringList getChildIdList(QString groupId);
Q_SIGNALS:
	void rollback();
private:
	ResItem* getItem(QString id);
	void removeItem(ResItem* item);
private:
	QList<ResItem*> itemList_;
	QMap<QString, ResItem*> itemMap_;
};

#endif // ResManagement_h__
