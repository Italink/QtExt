#ifndef BindAdjuster_h__
#define BindAdjuster_h__

#include <functional>
#include <QMetaProperty>
#include <QHash>
#include "QWidgetEx\Adjuster\Adjuster.h"

class Adjuster;
class AdjusterFactory {
	typedef std::function<Adjuster*(QObject*,QMetaProperty)> CreateAdjuster;
	AdjusterFactory();
	static AdjusterFactory *getInstance();
public:
	static Adjuster* create(QObject* object = nullptr, QMetaProperty property = {});
private:
	QHash<int,CreateAdjuster> AdjusterCreator_;
};



#endif // BindAdjuster_h__
