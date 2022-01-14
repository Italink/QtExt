#ifndef ResGroupItem_h__
#define ResGroupItem_h__

#include "ResItem.h"
#include "QList"
#include "ResSingleItem.h"

class ResGroupItem :public ResItem {
public:
	ResGroupItem();
	~ResGroupItem();
	QList<ResSingleItem*> childList_;
	virtual QString getId() override;
private:
	int id;
	inline static QList<int> idList_;
	inline static QList<int> idStack_;
};

#endif // ResGroupItem_h__
