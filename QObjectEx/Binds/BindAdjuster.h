#ifndef BindAdjuster_h__
#define BindAdjuster_h__

#include <functional>
#include <QMetaType>
#include "QVariant"
#include <QMetaProperty>

#include "QWidgetEx\Adjuster\Adjuster.h"

class QVariant;

Adjuster* createAdjuster(QObject* object = nullptr, QMetaProperty property = {});

#endif // BindAdjuster_h__
