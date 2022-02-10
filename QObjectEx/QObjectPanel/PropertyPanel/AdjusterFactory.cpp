#include "AdjusterFactory.h"

#include <QVariant>
#include <QCheckBox>
#include <QMetaType>
#include <QPushButton>
#include <QLineEdit>

#include "QWidgetEx\Adjuster\Adjuster.h"
#include "QWidgetEx\Adjuster\BoolBox.h"
#include "QWidgetEx\Adjuster\ByteArrayLoader.h"
#include "QWidgetEx\Adjuster\Color\ColorButton.hpp"
#include "QWidgetEx\Adjuster\Color\ColorDialog.hpp"
#include "QWidgetEx\Adjuster\Color\ColorsButton.hpp"
#include "QWidgetEx\Adjuster\Color\ColorsDialog.hpp"
#include "QWidgetEx\Adjuster\ComboBox.h"
#include "QWidgetEx\Adjuster\DoubleBox.h"
#include "QWidgetEx\Adjuster\DoubleSlider.h"
#include "QWidgetEx\Adjuster\ImageLoader.h"
#include "QWidgetEx\Adjuster\IntBox.h"
#include "QWidgetEx\Adjuster\IntSlider.h"
#include "QWidgetEx\Adjuster\LineEdit.h"
#include "QWidgetEx\Adjuster\RangeSlider.h"
#include "QWidgetEx\Adjuster\Vec2Box.h"
#include "QWidgetEx\Adjuster\Vec3Box.h"
#include "QWidgetEx\Adjuster\Vec4Box.h"
#include "QWidgetEx\Effect\QNeumorphism.h"
#include "QTypeEx/QBoundedDouble.h"
#include "QTypeEx/QBoundedInt.h"
#include "QTypeEx/QColors.h"

class PropertyAssignCommand :public QUndoCommand {
public:
	PropertyAssignCommand(QObject* obejct, QString propertyName,QVariant post)
		: obejct_(obejct)
		, propertyName_(propertyName)
		, post_(post)
	{
		pre_ = obejct_->property(propertyName_.toLocal8Bit());
		QString varStr = QDebug::toString(pre_);
		int index = varStr.indexOf(",");
		varStr = varStr.mid(index + 1, varStr.size() - index - 2);
		setText(QString("Property[%1]:  %2 ").arg(propertyName_).arg(varStr));
	}
public:
	QVariant pre_;	//��ֵǰ
	QVariant post_;	//��ֵ��
	QObject* obejct_;
	QString propertyName_;
	void undo() override {
		obejct_->setProperty(propertyName_.toLocal8Bit(), pre_);
	}
	void redo() override {
		obejct_->setProperty(propertyName_.toLocal8Bit(), post_);
	}
};

void notifyValueChanged(QObject* object, QString propertyName, QVariant var) {
	if (AdjusterFactory::isUpdating_)
		return;
	QVariant pre = object->property(propertyName.toLocal8Bit());
	if (QObjectEx::undoStack_.count() != 0) {
		PropertyAssignCommand* command = dynamic_cast<PropertyAssignCommand*>(const_cast<QUndoCommand*>(QObjectEx::undoStack_.command(QObjectEx::undoStack_.index() - 1)));
		if (command && command->propertyName_ == propertyName) {
			command->post_ = var;
			object->setProperty(propertyName.toLocal8Bit(), var);
		}
		else
			QObjectEx::undoStack_.push(new PropertyAssignCommand(object, propertyName,var));
	}
	else {
		QObjectEx::undoStack_.push(new PropertyAssignCommand(object, propertyName,var));
	}
}

#define BIND_ADJUSTER(Type,Adjuster) \
	AdjusterCreator_[QMetaTypeId2<Type>::qt_metatype_id()] = [](QObject* object,QString propertyName) {\
		Adjuster * adjuster = new Adjuster(object->property(propertyName.toLocal8Bit()).value<Type>()); \
		QObject::connect(adjuster,&Adjuster::valueChanged,object,[=](QVariant var){	\
			notifyValueChanged(object,propertyName,var);\
		});	\
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
	BIND_ADJUSTER(QByteArray, ByteArrayLoader);
	BIND_ADJUSTER(QImage, ImageLoader);
}

AdjusterFactory* AdjusterFactory::getInstance()
{
	static AdjusterFactory instance;
	return &instance;
}

Adjuster* AdjusterFactory::create(QObject* object /*= nullptr*/, QMetaProperty property /*= {}*/)
{
	Adjuster* adjuster = nullptr;
	if (property.isEnumType()) {
		QMetaEnum meta = property.enumerator();
		QStringList enumItems;
		for (int i = 0; i < meta.keyCount(); i++) {
			enumItems << meta.valueToKey(meta.value(i));
		}
		ComboBox* comboBox = new ComboBox(QCombo(meta.valueToKey(property.read(object).toInt()), enumItems));
		QObject::connect(comboBox, &Adjuster::valueChanged, object, [=](QVariant var) {
			QCombo combo = var.value<QCombo>();
			property.write(object, meta.value(combo.getCurrentIndex()));
		});
		adjuster = comboBox;
	}
	else if (getInstance()->AdjusterCreator_.contains(property.typeId())) {
		adjuster = getInstance()->AdjusterCreator_[property.typeId()](object, property.name());
		//if (adjuster != nullptr) {
		//	int index = adjuster->staticMetaObject.indexOfMethod("updateValue(QVariant)");
		//	QObject::connect(object, property.notifySignal(), adjuster, adjuster->metaObject()->method(index));
		//}
	}
	return adjuster;
}

Adjuster* AdjusterFactory::create(QObject* object /*= nullptr*/, QString propertyName /*= {}*/) {
	QVariant var = object->property(propertyName.toLocal8Bit().constData());
	if (getInstance()->AdjusterCreator_.contains(var.typeId())) {
		Adjuster* adjuster = getInstance()->AdjusterCreator_[var.typeId()](object, propertyName);
		return adjuster;
	}
	return nullptr;
}