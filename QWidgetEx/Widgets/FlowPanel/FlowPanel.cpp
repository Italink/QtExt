#include "FlowPanel.h"

FlowPanel::FlowPanel(){
	setViewMode(QListView::IconMode);
	setFrameShape(QFrame::NoFrame);
	setFlow(QListView::LeftToRight);
	setResizeMode(QListView::Adjust);
	setDragDropMode(QAbstractItemView::NoDragDrop);
	setIconSize(QSize(80, 80));
	setSpacing(10);
}

void FlowPanel::addItem(QString text, QIcon icon)
{
	QListWidgetItem* item = new QListWidgetItem;
	item->setText(text);
	item->setIcon(icon);
	item->setSizeHint(QSize(80, 100));
	item->setTextAlignment(Qt::AlignCenter);
	this->setTextElideMode(Qt::ElideRight);
	QListWidget::addItem(item);
}
