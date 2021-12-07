#include "ColorButton.hpp"
#include "QNeumorphism.h"
#include "ColorDialog.hpp"
#include <QPainter>

ColorButton::ColorButton(QColor color)
	: color_(color)
{
	setMinimumWidth(100);
	setFixedHeight(20);

	setColor(color);
	QObject::connect(this, &Button::clicked, this, [&]() {
		QWidgetEx::ColorDialog dialog;
		dialog.setColor(color_);
		QObject::connect(&dialog, &QWidgetEx::ColorDialog::colorChanged, this, [&](const QColor& color) {
			setColor(color);
			Q_EMIT valueChanged(QVariant::fromValue(color_));
			});
		dialog.exec();
		});
}

void ColorButton::setColor(QColor color)
{
	color_ = color;
	update();
}

void ColorButton::flush(QVariant var)
{
	QColor color = var.value<QColor>();
	if (color_ == color) {
		return;
	}
	setColor(color);
}

void ColorButton::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.fillRect(rect(),color_);
}
