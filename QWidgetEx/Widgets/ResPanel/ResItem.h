#ifndef ResItem_h__
#define ResItem_h__

#include <QObject>

class ResItem {
public:
	ResItem();
	virtual ~ResItem();
	virtual QString getId() = 0;
private:
};

#endif // ResItem_h__
