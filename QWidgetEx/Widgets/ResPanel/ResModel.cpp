#include "ResModel.h"
#include "ResGroupItem.h"
#include "QApplication"


ResModel::ResModel()
{
}

ResGroupItem* ResModel::createGroupItem()
{
	return new ResGroupItem;
}

bool ResModel::isGroup(QString id)
{
	return dynamic_cast<ResGroupItem*>(getItem(id)) != nullptr;
}

void ResModel::appendResItem(ResItem* item)
{
	insertResItem(itemList_.size(), item);
	rollback();
}

void ResModel::insertResItem(int index, ResItem* item)
{
	itemList_.insert(index, item);
	itemMap_[item->getId()] = item;
}

void ResModel::removeItems(QStringList idList)
{
	for (auto& id : idList) {
		removeItem(getItem(id));
	}
}

void ResModel::makeGroup(QStringList idList)
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
			sItemList << gItem->getChildList();
			gItem->clear();
			removeItem(gItem);
		}
	}
	for (auto& id : idList) {
		ResItem* item = getItem(id);
		itemList_.removeOne(item);
	}
	ResGroupItem* gItem = createGroupItem();
	for (auto& item : sItemList) {
		gItem->append(item);
	}
	insertResItem(minIndex, gItem);
	rollback();
}

void ResModel::takeApart(QString groupId)
{
	ResItem* item = getItem(groupId);
	int index = itemList_.indexOf(item);
	ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
	for (auto child : gItem->getChildList()) {
		insertResItem(index++, child);
	}
	gItem->clear();
	removeItem(item);
	rollback();
}

void ResModel::moveItem(int start, int end, int dst)
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

void ResModel::moveGroupChildItem(QString groupId, int start, int end, int dst)
{
	qDebug() << "copy" << (QApplication::keyboardModifiers() & Qt::ControlModifier);
	ResItem* item = getItem(groupId);
	ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
	for (int i = start; i <= end; i++) {
		gItem->insertItem(dst, gItem->childItem(i));
	}
	int removeIndex = start + (dst < start ? (end - start + 1) : 0);
	for (int i = 0; i <= end - start; i++) {
		gItem->removeItemByIndex(removeIndex);
	}
}

void ResModel::enterGroup(QString groupId, QStringList idList, int dstIndex)
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
			sItemList << gItem->getChildList();
			gItem->clear();
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
		gItem->insertItem(dstIndex, child);
	}
	rollback();
}

void ResModel::leaveGroup(QString groupId, QStringList idList, int dstIndex)
{
	qDebug() << "copy" << (QApplication::keyboardModifiers() & Qt::ControlModifier);
	ResItem* item = getItem(groupId);
	ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
	QList<ResSingleItem*> sItemList;
	for (auto& child : gItem->getChildList()) {
		if (idList.contains(child->getId()))
			sItemList << child;
	}
	for (auto child : sItemList) {
		insertResItem(dstIndex++, child);
		gItem->removeItem(child);
	}
	if (gItem->count()==0) {
		removeItem(gItem);
	}
	else if (gItem->count() == 1) {
		int index = itemList_.indexOf(item);
		insertResItem(index, gItem->childItem(0));
		gItem->removeItemByIndex(0);
		removeItem(gItem);
	}
	rollback();
}


QStringList ResModel::getIdList()
{
	QStringList list;
	for (auto& item : itemList_) {
		list << item->getId();
	}
	return list;
}

QStringList ResModel::getChildIdList(QString groupId)
{
	ResItem* item = getItem(groupId);
	ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
	QStringList list;
	for (auto& item : gItem->getChildList()) {
		list << item->getId();
	}
	return list;
}

ResItem* ResModel::getItemById(QString id)
{
	return itemMap_.value(id);
}

ResItem* ResModel::getItem(QString id)
{
	return itemMap_.value(id, nullptr);
}

void ResModel::removeItem(ResItem* item)
{
	ResGroupItem* gItem = dynamic_cast<ResGroupItem*>(item);
	if (gItem != nullptr) {
		for (auto& child : gItem->getChildList()) {
			removeItem(child);
		}
	}
	itemList_.removeOne(item);
	itemMap_.take(item->getId());
	delete item;
}