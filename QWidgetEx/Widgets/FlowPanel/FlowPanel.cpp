#include "FlowPanel.h"

FlowPanel::FlowPanel()
{
	setViewMode(QListView::IconMode);

	setFrameShape(QFrame::NoFrame);
	setFlow(QListView::LeftToRight);
	setResizeMode(QListView::Adjust);
	setDragDropMode(QAbstractItemView::NoDragDrop);
	addItem("2");
	addItem("3");
	addItem("4");
	QListWidgetItem* item = new QListWidgetItem;
	item->setText("hello");
	item->setIcon(QIcon(":/Icons/redo"));
	item->setFlags(item->flags()|Qt::ItemIsEditable);
	item->setSizeHint(QSize(80, 100));
	item->setTextAlignment(Qt::AlignCenter);
	this->setTextElideMode(Qt::ElideRight);
	setIconSize(QSize(80, 80));
	addItem(item);
	connect(this, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) {
		this->editItem(item);
	});

	
}

//void FlowPanel::addItem(QString text, QIcon icon)
//{
//
//}
//
