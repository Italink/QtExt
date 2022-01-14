#ifndef ResSingleItem_h__
#define ResSingleItem_h__

#include "ResItem.h"

class ResSingleItem :public ResItem {
public:
	ResSingleItem();
	~ResSingleItem();
	virtual QString getId() override;
private:
	int id;
	inline static QList<int> idList_;
	inline static QList<int> idStack_;
};

#endif // ResSingleItem_h__
