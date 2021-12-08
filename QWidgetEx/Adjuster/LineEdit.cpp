#include "LineEdit.h"
#include "QFocusLineEdit.h"

#include <QHBoxLayout>
#include "QNeumorphism.h"

LineEdit::LineEdit(QString str)
	:lineEdit_(new QFocusLineEdit())
{
	QNeumorphism* neum = new QNeumorphism;
	neum->setInset(true);
	setGraphicsEffect(neum);
	QHBoxLayout* h = new QHBoxLayout(this);
	h->setContentsMargins(0, 0, 0, 0);
	h->addWidget(lineEdit_);
	lineEdit_->setFixedHeight(20);
	lineEdit_->setText(str);
	lineEdit_->setFrame(QFrame::NoFrame);
	connect(lineEdit_, &QLineEdit::textChanged, this, [&](QString str) {
		Q_EMIT valueChanged(str);
		});
}

QVariant LineEdit::getValue()
{
	return lineEdit_->text();
}

void LineEdit::setValue(QVariant var)
{
	lineEdit_->setText(var.toString());
}