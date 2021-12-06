#include "QPropertyItem.h"
#include <QBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include "Binds\BindAdjuster.h"

QPropertyItem::QPropertyItem(QObject* object, QMetaProperty property)
	: object_(object)
	, property_(property)
	, itemWidget_(new QWidget)
	, name_(new QLabel)
{
	layout_ = new QHBoxLayout(itemWidget_);
	layout_->setAlignment(Qt::AlignCenter);
	layout_->setContentsMargins(10, 2, 10, 2);
	layout_->addWidget(name_, 100, Qt::AlignLeft);
	name_->setText(QString(property.name()).replace("_", " "));
	name_->setStyleSheet("background-color:rgba(0,0,0,0)");
	getter_ = [object, property](){
		return object->property(property.name());
	};

	setter_ = [object, property](QVariant var){
		object->setProperty(property.name(), var);
	};
}

QWidget* QPropertyItem::createWidget()
{
	if (setter_ == nullptr || getter_ == nullptr)
		return nullptr;
	return createAdjuster(property_.typeId(), getter_, setter_);
}

void QPropertyItem::setUp(QTreeWidgetItem* tree)
{
	layout_->addWidget(createWidget(), 0, Qt::AlignRight);
	tree->addChild(this);
	treeWidget()->setItemWidget(this, 0, itemWidget_);
}

void QPropertyItem::setUp(QTreeWidget* tree)
{
	layout_->addWidget(createWidget(),0,Qt::AlignRight);
	tree->addTopLevelItem(this);
	treeWidget()->setItemWidget(this, 0, itemWidget_);
}

void QPropertyItem::rename()
{
	QLineEdit* lineEdit = new QLineEdit;
	//treeWidget()->setItemWidget(this,0,lineEdit);
	//lineEdit->setText(text(0));
	//lineEdit->selectAll();
	//lineEdit->setFocus();
	//connect(lineEdit,&QLineEdit::editingFinished,this,[this,lineEdit](){
	//    QVariant var=getVar();
	//    ikObject_->setProperty(ikVar_.name(),QVariant());    //remove
	//    ikObject_->setProperty(lineEdit->text().toLocal8Bit().data(),var);
	//    int newIndex=ikObject_->metaObject()->indexOfProperty(lineEdit->text().toLocal8Bit().data());
	//    ikVar_=ikObject_->metaObject()->property(newIndex);
	//    treeWidget()->removeItemWidget(this,0);
	//    lineEdit->deleteLater();
	//});
}

