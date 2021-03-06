#include "FlowPanel.h"

FlowPanel::FlowPanel(){
	setViewMode(QListView::IconMode);
	setFrameShape(QFrame::NoFrame);
	setFlow(QListView::LeftToRight);
	setResizeMode(QListView::Adjust);
	setSelectionMode(QListView::SingleSelection);
	setDragDropMode(QAbstractItemView::NoDragDrop);
	setIconSize(QSize(80, 80));
	setSpacing(10);
	setStyleSheet("QListWidget{background-color : transparent; }");

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

QListWidgetItem* FlowPanel::getItem(QString name)
{
	for (int i = 0; i < count(); i++) {
		if (item(i)->text() == name)
			return item(i);
	}
	return nullptr;
}

