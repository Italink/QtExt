#include "RangeSlider.h"
#include "QFocusLineEdit.h"
#include "QNeumorphism.h"
#include <QValidator>
#include <QBoxLayout>
#include <QPainter>

RangeSlider::RangeSlider(QRange range, QWidget* parent /*= nullptr*/)
	: range_(range)
	, lowerEditer_(new QFocusLineEdit)
	, upperEditer_(new QFocusLineEdit)
{
	setFixedHeight(20);
	setGraphicsEffect(new QNeumorphism);

	lowerEditer_->setFixedHeight(height());
	lowerEditer_->setFrame(QFrame::NoFrame);
	lowerEditer_->setAlignment(Qt::AlignCenter);
	lowerEditer_->setValidator(new QDoubleValidator);
	lowerEditer_->setStyleSheet("background-color:transparent;");

	upperEditer_->setFixedHeight(height());
	upperEditer_->setFrame(QFrame::NoFrame);
	upperEditer_->setAlignment(Qt::AlignCenter);
	upperEditer_->setValidator(new QDoubleValidator);
	upperEditer_->setStyleSheet("background-color:transparent;");

	QHBoxLayout* h = new QHBoxLayout(this);
	h->setContentsMargins(0, 0, 0, 0);
	h->setSpacing(0);
	h->addWidget(lowerEditer_);
	h->addWidget(upperEditer_);
	setValue(QVariant::fromValue(range));
}

RangeSlider::~RangeSlider()
{
}

QVariant RangeSlider::getValue()
{
	return QVariant::fromValue<>(range_);
}

void RangeSlider::setValue(QVariant var)
{
	QRange range = var.value<QRange>();
	lowerEditer_->setText(QString::number(range.getLower()));
	upperEditer_->setText(QString::number(range.getUpper()));
}

void RangeSlider::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(200, 200, 200));
	painter.drawRoundedRect(rect(), 2, 2);
	QWidget::paintEvent(event);
}