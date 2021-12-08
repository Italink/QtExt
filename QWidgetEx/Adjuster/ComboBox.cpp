#include "ComboBox.h"
#include <QComboBox>
#include <QHBoxLayout>
#include "QNeumorphism.h"

ComboBox::ComboBox(QCombo value /*= 0*/, QWidget* parent /*= nullptr*/)
	: comboBox_(new QComboBox)
	, value_(value)
{
	for (auto& item : value.items_) {
		comboBox_->addItem(item);
	}
	comboBox_->setCurrentIndex(value.currentIndex_);
	QHBoxLayout* h = new QHBoxLayout(this);
	h->setContentsMargins(0, 0, 0, 0);
	h->addWidget(comboBox_);

	QNeumorphism* neum = new QNeumorphism;
	neum->setInset(true);
	setGraphicsEffect(neum);
	connect(comboBox_, &QComboBox::currentIndexChanged, this, [this](int index) {
		value_.currentIndex_ = index;
		Q_EMIT valueChanged(QVariant::fromValue(value_));
		});
}

QVariant ComboBox::getValue()
{
	return QVariant::fromValue(value_);
}

void ComboBox::setValue(QVariant var)
{
	value_ = var.value<QCombo>();
	comboBox_->setCurrentIndex(value_.currentIndex_);
}