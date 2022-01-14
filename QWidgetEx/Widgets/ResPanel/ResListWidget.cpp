#include "ResListWidget.h"
#include "qevent.h"
#include <QMimeData>
#include "QAbstractItemModel"

ResListWidget::ResListWidget() {
	this->setMovement(QListView::Free);
	this->setFlow(QListView::LeftToRight);
	this->setDragDropMode(QAbstractItemView::DragDrop);
	this->setDefaultDropAction(Qt::MoveAction);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setFrameShape(QFrame::NoFrame);
	this->setFixedHeight(30);
}

void ResListWidget::addItem(QString text)
{
	QListWidgetItem* item = new QListWidgetItem();
	item->setText(text);
	item->setSizeHint({ 30,26 });
	item->setTextAlignment(Qt::AlignCenter);
	QListWidget::addItem(item);
}

void ResListWidget::dropEvent(QDropEvent* event) {
	QListWidget::dropEvent(event);
	if (event->isAccepted()) {
		Q_EMIT dropItems(insertItems_);
		insertItems_.clear();
	}
}

void ResListWidget::rowsInserted(const QModelIndex& parent, int start, int end)
{
	for (int i = start; i <= end; i++) {
		insertItems_ << item(i);
	}
	QListWidget::rowsInserted(parent, start, end);
}
