#include "ResListWidget.h"
#include "qevent.h"
#include <QMimeData>
#include "QAbstractItemModel"

ResListWidget::ResListWidget() {
	this->setMovement(QListView::Free);
	this->setFlow(QListView::LeftToRight);
	this->setDragDropMode(QAbstractItemView::DragDropMode::DragDrop);
	this->setDefaultDropAction(Qt::MoveAction);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setFrameShape(QFrame::NoFrame);
	this->setFixedHeight(25);
}

void ResListWidget::addItem(QString text)
{
	QListWidgetItem* item = new QListWidgetItem();
	item->setText(text);
	item->setSizeHint({ 25,22 });
	item->setTextAlignment(Qt::AlignCenter);
	QListWidget::addItem(item);
	insertItems_.clear();
}

void ResListWidget::dropEvent(QDropEvent* event) {
	QListWidget::dropEvent(event);
	if (event->isAccepted()) {
		if(!insertItems_.isEmpty())
			Q_EMIT dropItems(dstIndex_, insertItems_);
		insertItems_.clear();
	}
}

void ResListWidget::rowsInserted(const QModelIndex& parent, int start, int end)
{
	for (int i = start; i <= end; i++) {
		insertItems_ << item(i);
	}
	dstIndex_ = start;
	QListWidget::rowsInserted(parent, start, end);
}

void ResListWidget::startDrag(Qt::DropActions supportedActions)
{
	QListWidget::startDrag(Qt::DropAction::MoveAction);
}