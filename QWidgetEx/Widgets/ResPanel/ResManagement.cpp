#include "ResManagement.h"
#include "ResGroupItem.h"

ResManagement::ResManagement()
{
	addNewSingleItem();
	addNewSingleItem();
	addNewSingleItem();
	addNewSingleItem();
	addNewSingleItem();
}

bool ResManagement::isGroup(QString id)
{
	return dynamic_cast<ResGroupItem*>(getItem(id)) != nullptr;
}

void ResManagement::addNewSingleItem()
{
	ResSingleItem* item = new ResSingleItem;
	addResItem(itemList_.size(), item);
}

void ResManagement::addResItem(int index, ResItem* item)
{
	itemList_.insert(index, item);
	itemMap_[item->getId()] = item;
}

void ResManagement::removeItems(QStringList idList)
{
	for (auto& id : idList) {
		removeItem(getItem(id));
	}
}

void ResManagement::makeGroup(QStringList idList)
{
	QList<ResSingleItem*> sItemList;
	for (auto& id : idList) {
		ResSingleItem* sItem = dynamic_cast<ResSingleItem*>(getItem(id));
		if (sItem != nullptr) {
			sItemList << sItem;
		}
		else {
			ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(getItem(id));
			sItemList << gItem->childList_;
			gItem->childList_.clear();
			removeItem(gItem);
		}
	}
	ResGroupItem* gItem = new ResGroupItem;
	gItem->childList_ = sItemList;
}

void ResManagement::takePart(QString groupId)
{
}

void ResManagement::moveItem(int start, int end, int dst)
{
	for (int i = start; i <= end; i++) {
		itemList_.insert(dst, itemList_[i]);
	}
	int removeIndex = start + (dst < start ? (end - start + 1) : 0);
	for (int i = 0; i <= end - start; i++) {
		itemList_.removeAt(removeIndex);
	}
	Q_EMIT rollback();
}

void ResManagement::moveGroupChildItem(QString groupId, int start, int end, int dst)
{
}

//void ResManagement::resort(QStringList idList)
//{
//}
//
//void ResManagement::resort(QString groupId, QStringList idList)
//{
//}

QStringList ResManagement::getIdList()
{
	QStringList list;
	for (auto& item : itemList_) {
		list << item->getId();
	}
	return list;
}

QStringList ResManagement::getChildIdList(QString groupId)
{
	ResItem* item = getItem(groupId);
	ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
	QStringList list;
	for (auto& item : gItem->childList_) {
		list << item->getId();
	}
	return list;
}

ResItem* ResManagement::getItem(QString id)
{
	return itemMap_.value(id, nullptr);
}

void ResManagement::removeItem(ResItem* item)
{
	ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
	if (gItem != nullptr) {
		for (auto& child : gItem->childList_) {
			removeItem(child);
		}
	}
	itemList_.removeOne(item);
	itemMap_.take(item->getId());
	item->deleteLater();
}