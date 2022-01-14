#include "ResSingleItem.h"

ResSingleItem::ResSingleItem() {
	if (idStack_.empty()) {
		this->id = idList_.size();
	}
	else {
		this->id = idStack_.takeFirst();
	}
	idList_.push_back(this->id);
}

ResSingleItem::~ResSingleItem() {
	idStack_.push_back(this->id);
	idList_.removeOne(this->id);
}

QString ResSingleItem::getId()
{
	return QString::number(id + 1);
}