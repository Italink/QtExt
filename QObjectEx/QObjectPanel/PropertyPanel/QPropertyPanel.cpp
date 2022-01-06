#include "QPropertyPanel.h"
#include <QApplication>
#include <QMetaProperty>
#include "QPropertyItem.h"
#include "QFile"

QPropertyPanel::QPropertyPanel(QObject* object /*= nullptr*/) {
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

QObject* QPropertyPanel::getObject() const
{
	return object_;
}

void QPropertyPanel::setObject(QObject* val) {
	if (val != object_) {
		object_ = val;
		updatePanel();
	}
}

void setupItemInternal(QObject* object, QPropertyItem* parentItem) {
	if (object == nullptr)
		return;

	for (int i = object->metaObject()->propertyOffset(); i < object->metaObject()->propertyCount(); i++) {
		QMetaProperty property = object->metaObject()->property(i);
		QPropertyItem* item = new QPropertyItem(object, property);
		item->setUp(parentItem);

		const QMetaObject* meta = property.metaType().metaObject();
		if (meta != nullptr && meta->inherits(&QObject::staticMetaObject)) {
			QObject* obj = property.read(object).value<QObject*>();
			if (obj != nullptr) {
				setupItemInternal(obj, item);
			}
		}
	}
}

void QPropertyPanel::updatePanel() {
	this->clear();
	if (object_ == nullptr)
		return;
	for (int i = object_->metaObject()->propertyOffset(); i < object_->metaObject()->propertyCount(); i++) {
		QMetaProperty property = object_->metaObject()->property(i);
		QPropertyItem* item = new QPropertyItem(object_, property);
		item->setUp(this);

		const QMetaObject* meta = property.metaType().metaObject();

		if (meta != nullptr && meta->inherits(&QObject::staticMetaObject)) {
			QObject* obj = property.read(object_).value<QObject*>();
			if (obj != nullptr) {
				setupItemInternal(obj, item);
			}
		}
	}
	this->expandAll();
}