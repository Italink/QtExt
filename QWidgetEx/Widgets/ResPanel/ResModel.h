#ifndef ResModel_h__
#define ResModel_h__

#include "QObject"
#include "ResItem.h"
#include "QMap"

class ResSingleItem;
class ResGroupItem;

class ResModel :public QObject {
	Q_OBJECT
public:
	ResModel();
	bool isGroup(QString id);
	void appendResItem(ResItem* item);
	void insertResItem(int index, ResItem* item);
	void removeItems(QStringList idList);
	void makeGroup(QStringList idList);
	void takeApart(QString groupId);
	void moveItem(int start, int end, int dst);
	void moveGroupChildItem(QString groupId, int start, int end, int dst);
	void enterGroup(QString groupId, QStringList idList, int dstIndex);
	void leaveGroup(QString groupId, QStringList idList, int dstIndex);
	QStringList getIdList();
	QStringList getChildIdList(QString groupId);
	ResItem* getItemById(QString id);
protected:
	virtual ResGroupItem* createGroupItem();
Q_SIGNALS:
	void rollback();
private:
	ResItem* getItem(QString id);
	void removeItem(ResItem* item);
protected:
	QList<ResItem*> itemList_;
	QMap<QString, ResItem*> itemMap_;
};

#endif // ResModel_h__

