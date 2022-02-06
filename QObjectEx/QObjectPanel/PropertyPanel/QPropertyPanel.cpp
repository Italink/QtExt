#include "QPropertyPanel.h"
#include <QApplication>
#include <QMetaProperty>
#include "QPropertyItem.h"
#include "QFile"
#include "QDynamicPropertyItem.h"

QPropertyPanel::QPropertyPanel(QObjectEx* object /*= nullptr*/) {
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
		" background-color: rgba(255,255,255,0);"
		"}"
	);
}

QObjectEx* QPropertyPanel::getObject() const
{
	return object_;
}

void QPropertyPanel::setObject(QObjectEx* val) {
	if (val != object_) {
		object_ = val;
		updatePanel();
	}
}

void setupItemInternal(QObjectEx* object, QTreeWidgetItem* parentItem) {
	if (object == nullptr)
		return;

	for (int i = object->metaObject()->propertyOffset(); i < object->metaObject()->propertyCount(); i++) {
		QMetaProperty property = object->metaObject()->property(i);
		QPropertyItem* item = new QPropertyItem(object, property);
		item->setUp(parentItem);

		const QMetaObject* meta = property.metaType().metaObject();
		if (meta != nullptr && meta->inherits(&QObject::staticMetaObject)) {
			QObjectEx* obj = property.read(object).value<QObjectEx*>();
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

		if (meta != nullptr && meta->inherits(&QObjectEx::staticMetaObject)) {
			QObjectEx* obj = property.read(object_).value<QObjectEx*>();
			if (obj != nullptr) {
				setupItemInternal(obj, item);
			}
		}
	}
	this->expandAll();

	for (auto& dpName : object_->dynamicPropertyNames()) {
		QDynamicPropertyItem* item = new QDynamicPropertyItem(object_, dpName);
		item->setUp(this);
		QVariant var = object_->property(dpName);
		const QMetaObject* meta = var.metaType().metaObject();
		if (meta != nullptr && meta->inherits(&QObjectEx::staticMetaObject)) {
			QObjectEx* obj = var.value<QObjectEx*>();
			if (obj != nullptr) {
				setupItemInternal(obj, item);
			}
		}
	}
}