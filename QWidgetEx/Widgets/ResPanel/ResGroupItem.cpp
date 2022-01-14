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