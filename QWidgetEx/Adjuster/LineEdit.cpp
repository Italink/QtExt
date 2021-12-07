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
	QHBoxLayout *h = new QHBoxLayout(this);
	h->setContentsMargins(0,0,0,0);
	h->addWidget(lineEdit_);
	lineEdit_->setFixedHeight(20);
	lineEdit_->setText(str);
	lineEdit_->setFrame(QFrame::NoFrame);
	connect(lineEdit_,&QLineEdit::textChanged,this,[&](QString str){
		Q_EMIT valueChanged(str);
	});
}

void LineEdit::flush(QVariant var)
{
	QString text = var.toString();
	if (text != lineEdit_->text()) {
		lineEdit_->setText(text);
	}
}

