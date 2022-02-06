#ifndef ResGroupItem_h__
#define ResGroupItem_h__

#include "ResItem.h"
#include "QList"
#include "ResSingleItem.h"

class ResGroupItem :public ResItem {
public:
	ResGroupItem();
	virtual ~ResGroupItem() override;
	virtual QString getId() override;
	
	virtual void clear();
	virtual void insertItem(int index, ResSingleItem* item);
	virtual void removeItem(ResSingleItem* item);
	
	void append(ResSingleItem* item);
	void removeItemByIndex(int index);
	int count();
	QList<ResSingleItem*> getChildList() const;
	ResSingleItem* childItem(int index);

private:
	int id;
	inline static QList<int> idList_;
	inline static QList<int> idStack_;
	QList<ResSingleItem*> childList_;
};

#endif // ResGroupItem_h__
