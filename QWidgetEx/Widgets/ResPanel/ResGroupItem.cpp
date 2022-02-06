#include "ResGroupItem.h"

ResGroupItem::ResGroupItem()
{
	if (idStack_.empty()) {
		this->id = idList_.size();
	}
	else {
		this->id = idStack_.takeFirst();
	}
	idList_.push_back(this->id);
}

ResGroupItem::~ResGroupItem()
{
	idStack_.push_back(this->id);
	idList_.removeOne(this->id);
}

QString ResGroupItem::getId()
{
	return QString(QChar('A' + id));
}

void ResGroupItem::clear()
{
	childList_.clear();
}

void ResGroupItem::insertItem(int index, ResSingleItem* item)
{
	childList_.insert(index, item);
}

void ResGroupItem::removeItem(ResSingleItem* item)
{
	childList_.removeOne(item);
}

void ResGroupItem::append(ResSingleItem* item)
{
	insertItem(childList_.size(), item);
}

void ResGroupItem::removeItemByIndex(int index)
{
	childList_.removeAt(index);
}

int ResGroupItem::count()
{
	return childList_.size();
}

QList<ResSingleItem*> ResGroupItem::getChildList() const
{
	return childList_;
}

ResSingleItem* ResGroupItem::childItem(int index)
{
	return childList_.value(index);
}
