#include "ResManagement.h"
#include "ResGroupItem.h"
#include "QApplication"

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
	int minIndex =itemList_.size();
	for (auto& id : idList) {
		ResItem* item = getItem(id);
		minIndex = qMin(minIndex, itemList_.indexOf(item));
		ResSingleItem* sItem = dynamic_cast<ResSingleItem*>(item);
		if (sItem != nullptr) {
			sItemList << sItem;
		}
		else {
			ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
			sItemList << gItem->childList_;
			gItem->childList_.clear();
			removeItem(gItem);
		}
	}
	for (auto& id : idList) {
		ResItem* item = getItem(id);
		itemList_.removeOne(item);
	}
	ResGroupItem* gItem = new ResGroupItem;
	gItem->childList_ = sItemList;
	addResItem(minIndex, gItem);
	rollback();
}

void ResManagement::takeApart(QString groupId)
{
	ResItem* item = getItem(groupId);
	int index = itemList_.indexOf(item);
	ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
	for (auto child : gItem->childList_) {
		addResItem(index++, child);
	}
	gItem->childList_.clear();
	removeItem(item);
	rollback();
}

void ResManagement::moveItem(int start, int end, int dst)
{
	qDebug() << "copy" << (QApplication::keyboardModifiers() & Qt::ControlModifier);
	for (int i = start; i <= end; i++) {
		itemList_.insert(dst, itemList_[i]);
	}
	int removeIndex = start + (dst < start ? (end - start + 1) : 0);
	for (int i = 0; i <= end - start; i++) {
		itemList_.removeAt(removeIndex);
	}
}

void ResManagement::moveGroupChildItem(QString groupId, int start, int end, int dst)
{
	qDebug() << "copy" << (QApplication::keyboardModifiers() & Qt::ControlModifier);
	ResItem* item = getItem(groupId);
	ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
	for (int i = start; i <= end; i++) {
		gItem->childList_.insert(dst, gItem->childList_[i]);
	}
	int removeIndex = start + (dst < start ? (end - start + 1) : 0);
	for (int i = 0; i <= end - start; i++) {
		gItem->childList_.removeAt(removeIndex);
	}
}

void ResManagement::enterGroup(QString groupId, QStringList idList, int dstIndex)
{
	qDebug() << "copy" << (QApplication::keyboardModifiers() & Qt::ControlModifier);
	QList<ResSingleItem*> sItemList;
	for (auto& id : idList) {
		ResItem* item = getItem(id);
		ResSingleItem* sItem = dynamic_cast<ResSingleItem*>(item);
		if (sItem != nullptr) {
			sItemList << sItem;
		}
		else {
			ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
			sItemList << gItem->childList_;
			gItem->childList_.clear();
			removeItem(gItem);
		}
	}
	for (auto& id : idList) {
		ResItem* item = getItem(id);
		itemList_.removeOne(item);
	}
	ResItem* item = getItem(groupId);
	ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
	for (auto child : sItemList) {
		gItem->childList_.insert(dstIndex, child);
	}
	rollback();
}

void ResManagement::leaveGroup(QString groupId, QStringList idList, int dstIndex)
{
	qDebug() << "copy" << (QApplication::keyboardModifiers() & Qt::ControlModifier);
	ResItem* item = getItem(groupId);
	ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
	QList<ResSingleItem*> sItemList;
	for (auto& child : gItem->childList_) {
		if (idList.contains(child->getId()))
			sItemList << child;
	}
	for (auto child : sItemList) {
		addResItem(dstIndex++, child);
		gItem->childList_.removeOne(child);
	}
	if (gItem->childList_.isEmpty()) {
		removeItem(gItem);
	}
	else if (gItem->childList_.size() == 1) {
		int index = itemList_.indexOf(item);
		addResItem(index, gItem->childList_.takeFirst());
		removeItem(gItem);
	}
	rollback();
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