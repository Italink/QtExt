#include "BindAdjuster.h"

#include <QVariant>
#include <QCheckBox>
#include <QMetaType>
#include <QPushButton>
#include <QLineEdit>

#include "QWidgetEx\Adjuster\NumberBox.h"
#include "QTypeEx\QSliderNumber.h"
#include "QWidgetEx\Adjuster\NumberSlider.h"
#include "QWidgetEx\Adjuster\Color\ColorDialog.hpp"
#include "QTypeEx\QColors.h"
#include "QWidgetEx\Adjuster\Color\ColorsDialog.hpp"
#include "QWidgetEx\Effect\QNeumorphism.h"


#define BIND_ADJUSTER(Type) case QMetaTypeId2<Type>::qt_metatype_id():

constexpr int turnConst(const int id) {
	return id;
}

const int QColorID = QMetaTypeId2<QGradientStops>::qt_metatype_id();

QWidget* createAdjuster(int typeId, Getter getter, Setter setter){

	switch (typeId){
	BIND_ADJUSTER(int) {
		NumberBox* numberBox = new NumberBox(getter().toDouble(), 0);
		QObject::connect(numberBox, &NumberBox::valueChanged, numberBox, [=](double var) {
			setter(QVariant(var));
			});
		return numberBox;
	}

	BIND_ADJUSTER(float){
		NumberBox* numberBox = new NumberBox(getter().toDouble(), 3);
		QObject::connect(numberBox, &NumberBox::valueChanged, numberBox, [=](double var) {
			setter(QVariant(var));
			});
		return numberBox;
	}

	BIND_ADJUSTER(double) {
		NumberBox* numberBox = new NumberBox(getter().toDouble(), 3);
		QObject::connect(numberBox, &NumberBox::valueChanged, numberBox, [=](double var) {
			setter(QVariant(var));
			});
		return numberBox;
	}

	BIND_ADJUSTER(bool) {
		QCheckBox* box = new QCheckBox();
		box->setChecked(getter().toBool() ? Qt::Checked : Qt::Unchecked);
		QObject::connect(box, &QCheckBox::toggled, box, [=](bool var) {
			setter(var);
			});
		return box;
	}

	BIND_ADJUSTER(QString) {
		QLineEdit* edit = new QLineEdit(getter().toString());
		QObject::connect(edit, &QLineEdit::textChanged, edit, [=](QString var) {
			setter(var);
			});
		return edit;
	}

	BIND_ADJUSTER(QSliderNumber) {
		QSliderNumber number = getter().value<QSliderNumber>();
		NumberSlider* slider = new NumberSlider(number.number(), number.min(), number.max(), number.precision());
		QObject::connect(slider, &NumberSlider::valueChanged, slider, [=](double value) {
			QSliderNumber number = getter().value<QSliderNumber>();
			number.setNumber(value);
			setter(QVariant::fromValue<>(number));
			});
		return slider;
	}

	BIND_ADJUSTER(QColor) {
		QPushButton* btColor = new  QPushButton;
		btColor->setMinimumWidth(100);
		btColor->setAutoFillBackground(true);
		btColor->setFlat(true);
		btColor->setFixedWidth(100);
		QPalette pal;
		pal.setColor(QPalette::ColorRole::Button, getter().value<QColor>());
		btColor->setPalette(pal);
		QObject::connect(btColor, &QPushButton::clicked, btColor, [=]() {
			ColorWidgets::ColorDialog dialog;
			dialog.setColor(getter().value<QColor>());
			QObject::connect(&dialog, &ColorWidgets::ColorDialog::colorChanged, btColor, [=](const QColor& color) {
				setter(QVariant::fromValue<>(color));
				QPalette pal;
				pal.setColor(QPalette::ColorRole::Button, color);
				btColor->setPalette(pal);
				});
			dialog.exec();
			});
		return btColor;
	}

	BIND_ADJUSTER(QColors) {
		QPushButton* btColor = new QPushButton;
		QNeumorphism * neum = new QNeumorphism;
		btColor->setGraphicsEffect(neum);
		btColor->setMinimumWidth(100);
		btColor->setAutoFillBackground(true);
		btColor->setFlat(true);
		btColor->setFixedWidth(100);
		QPalette pal;
		QLinearGradient linearGradient;
		linearGradient.setStops(getter().value<QColors>().getStops());
		linearGradient.setStart({0,0});
		linearGradient.setFinalStop({(qreal)btColor->width(),0.0});
		pal.setBrush(QPalette::ColorRole::Button,linearGradient);
		btColor->setPalette(pal);
		QObject::connect(btColor, &QPushButton::clicked, btColor, [=]() {
			ColorWidgets::ColorsDialog dialog;
			dialog.setColors(getter().value<QColors>().getStops());
			QObject::connect(&dialog, &ColorWidgets::ColorsDialog::colorsChanged, btColor, [=](const QGradientStops& stops) {
				QPalette pal;
				QLinearGradient linearGradient;
				linearGradient.setStops(stops);
				linearGradient.setStart({ 0,0 });
				linearGradient.setFinalStop({ (qreal)btColor->width(),0.0 });
				pal.setBrush(QPalette::ColorRole::Button, linearGradient);
				btColor->setPalette(pal);
				setter(QVariant::fromValue<>( QColors(stops)));
				});
			dialog.exec();
			});
		return btColor;
	}

	}
	return nullptr;
}


