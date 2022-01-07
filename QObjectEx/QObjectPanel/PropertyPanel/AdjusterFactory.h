#ifndef BindAdjuster_h__
#define BindAdjuster_h__

#include <functional>
#include <QMetaProperty>
#include <QHash>
#include "QWidgetEx\Adjuster\Adjuster.h"
#include "QObjectEx\QObjectEx.h"

class Adjuster;

class AdjusterFactory {
	typedef std::function<Adjuster* (QObjectEx*, QString propertyName)> CreateAdjuster;
	AdjusterFactory();
	static AdjusterFactory* getInstance();
public:
	static Adjuster* create(QObjectEx* object = nullptr, QMetaProperty property = {});
	static Adjuster* create(QObjectEx* object = nullptr, QString propertyName = "");
private:
	QHash<int, CreateAdjuster> AdjusterCreator_;
};

#endif // BindAdjuster_h__
