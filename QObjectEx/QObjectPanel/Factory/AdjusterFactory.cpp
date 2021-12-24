#include "AdjusterFactory.h"

#include <QVariant>
#include <QCheckBox>
#include <QMetaType>
#include <QPushButton>
#include <QLineEdit>

#include "Adjuster\Color\ColorDialog.hpp"
#include "QColors.h"
#include "Adjuster\Color\ColorsDialog.hpp"
#include "Effect\QNeumorphism.h"
#include "Adjuster\IntBox.h"
#include "Adjuster\DoubleBox.h"
#include "QBoundedDouble.h"
#include "Adjuster\DoubleSlider.h"
#include "QBoundedInt.h"
#include "Adjuster\IntSlider.h"
#include "Adjuster\Adjuster.h"
#include "Adjuster\Color\ColorsButton.hpp"
#include "Adjuster\Color\ColorButton.hpp"
#include "Adjuster\BoolBox.h"
#include "Adjuster\LineEdit.h"
#include "Adjuster\Vec4Box.h"
#include "Adjuster\Vec3Box.h"
#include "Adjuster\Vec2Box.h"
#include "Adjuster\ComboBox.h"
#include "Adjuster\RangeSlider.h"

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

AdjusterFactory::AdjusterFactory() {
	BIND_ADJUSTER(double, DoubleBox);
	BIND_ADJUSTER(float, DoubleBox);
	BIND_ADJUSTER(int, IntBox);
	BIND_ADJUSTER(bool, BoolBox);
	BIND_ADJUSTER(QString, LineEdit);
	BIND_ADJUSTER(QBoundedDouble, DoubleSlider);
	BIND_ADJUSTER(QBoundedInt, IntSlider);
	BIND_ADJUSTER(QColor, ColorButton);
	BIND_ADJUSTER(QColors, ColorsButton);
	BIND_ADJUSTER(QVector2D, Vec2Box);
	BIND_ADJUSTER(QVector3D, Vec3Box);
	BIND_ADJUSTER(QVector4D, Vec4Box);
	BIND_ADJUSTER(QCombo, ComboBox);
	BIND_ADJUSTER(QRange, RangeSlider);
}

AdjusterFactory* AdjusterFactory::getInstance()
{
	static AdjusterFactory instance;
	return &instance;
}

Adjuster* AdjusterFactory::create(QObject* object /*= nullptr*/, QMetaProperty property /*= {}*/)
{
	if (property.isEnumType()) {
		QMetaEnum meta = property.enumerator();
		QStringList enumItems;
		for (int i = 0; i < meta.keyCount(); i++) {
			enumItems << meta.valueToKey(meta.value(i));
		}
		ComboBox* comboBox = new ComboBox(QCombo(meta.valueToKey(property.read(object).toInt()), enumItems));
		QObject::connect(comboBox, &Adjuster::valueChanged, object, [=](QVariant var) {
			QCombo combo = var.value<QCombo>();
			property.write(object, meta.value(combo.currentIndex_));
		});

		int index = comboBox->staticMetaObject.indexOfMethod("flush(QVariant)");
		//QObject::connect(object, property.notifySignal(), comboBox, comboBox->metaObject()->method(index));
		return comboBox;
	}
	else if (getInstance()->AdjusterCreator_.contains(property.typeId())) {
		return getInstance()->AdjusterCreator_[property.typeId()](object, property);
	}

	return nullptr;
}