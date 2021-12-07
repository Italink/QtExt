#include "QObejctPanel.h"
#include <QApplication>
#include <QMetaProperty>
#include "QPropertyItem.h"
#include "QFile"
#include "QObjectEx.h"

QObjectPanel::QObjectPanel(QObject* object /*= nullptr*/){
	setObject(object);
	setColumnCount(1);      
	setIndentation(8);
	setHeaderHidden(true);
	setContextMenuPolicy(Qt::CustomContextMenu);
	setColumnWidth(0, 120);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setFrameStyle(QFrame::NoFrame);
	connect(this, &QTreeWidget::itemPressed, this, [](QTreeWidgetItem* item, int) {
		if (qApp->mouseButtons() & Qt::RightButton) {
			/*show menu*/
		}
		});
	setStyleSheet(
		"QTreeView{"
		" background-color: rgb(255,255,255);"
		"}"
	);
}

QObject* QObjectPanel::getObject() const
{
	return object_;
}

void QObjectPanel::setObject(QObject* val){
	if (val != object_) {
		object_ = val;
		Q_EMIT objectChanged(object_);
		updatePanel();
	}
}

void QObjectPanel::updatePanel(){
	this->clear();
	if(object_ == nullptr)
		return;
	for (int i = object_->metaObject()->propertyOffset(); i < object_->metaObject()->propertyCount(); i++) {
		QMetaProperty property = object_->metaObject()->property(i);
		QPropertyItem *item = new QPropertyItem(object_, property);
		if (item) {
			item->setUp(this);
		}
	}
}

void QObjectPanel::closeEvent(QCloseEvent* event)
{
	QFile file("test.txt");
	file.open(QFile::WriteOnly);
	file.write(QObjectEx::dump(object_));
	file.close();
}

