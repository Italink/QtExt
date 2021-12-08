#include "AdjusterFactory.h"

#include <QVariant>
#include <QCheckBox>
#include <QMetaType>
#include <QPushButton>
#include <QLineEdit>

#include "QWidgetEx\Adjuster\Color\ColorDialog.hpp"
#include "QTypeEx\QColors.h"
#include "QWidgetEx\Adjuster\Color\ColorsDialog.hpp"
#include "QWidgetEx\Effect\QNeumorphism.h"
#include "QWidgetEx\Adjuster\IntBox.h"
#include "QWidgetEx\Adjuster\DoubleBox.h"
#include "QTypeEx\QBoundedDouble.h"
#include "QWidgetEx\Adjuster\DoubleSlider.h"
#include "QTypeEx\QBoundedInt.h"
#include "QWidgetEx\Adjuster\IntSlider.h"
#include "QWidgetEx\Adjuster\Adjuster.h"
#include "QWidgetEx\Adjuster\Color\ColorsButton.hpp"
#include "QWidgetEx\Adjuster\Color\ColorButton.hpp"
#include "QWidgetEx\Adjuster\BoolBox.h"
#include "QWidgetEx\Adjuster\LineEdit.h"


#define BIND_ADJUSTER(Type,Adjuster) \
	AdjusterCreator_[QMetaTypeId2<Type>::qt_metatype_id()] = [](QObject* object,QMetaProperty property) {\
		Adjuster * adjuster = new Adjuster(property.read(object).value<Type>()); \
		QObject::connect(adjuster,&Adjuster::valueChanged,object,[=](QVariant var){	\
			property.write(object,QVariant::fromValue(var)); \
		});	\
		int index = adjuster->staticMetaObject.indexOfMethod("flush(QVariant)"); \
	    QObject::connect(object, property.notifySignal(), adjuster, adjuster->metaObject()->method(index)); \
		return adjuster;\
	};

AdjusterFactory::AdjusterFactory()
{
	BIND_ADJUSTER(double, DoubleBox)
	BIND_ADJUSTER(float, DoubleBox)
	BIND_ADJUSTER(int, IntBox)
	BIND_ADJUSTER(bool, BoolBox)
	BIND_ADJUSTER(QString, LineEdit)
	BIND_ADJUSTER(QBoundedDouble, DoubleSlider)
	BIND_ADJUSTER(QBoundedInt, IntSlider)
	BIND_ADJUSTER(QColor, ColorButton)
	BIND_ADJUSTER(QColors, ColorsButton)
}

AdjusterFactory* AdjusterFactory::getInstance()
{
	static AdjusterFactory instance;
	return &instance;
}

Adjuster* AdjusterFactory::create(QObject* object /*= nullptr*/, QMetaProperty property /*= {}*/)
{
	if (getInstance()->AdjusterCreator_.contains(property.typeId())) {
		return getInstance()->AdjusterCreator_[property.typeId()](object,property);
	}
	else {
		return nullptr;
	}
}
