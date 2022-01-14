#include "ResPanel.h"
#include "QBoxLayout"
#include "ResGroupItem.h"
#include "ResManagement.h"
#include <QApplication>
#include "QMenu"

ResPanel::ResPanel() {
	resManagement_ = new ResManagement;
	QVBoxLayout* v = new QVBoxLayout(this);
	v->setSpacing(0);
	v->addWidget(&topWidget_);
	v->addWidget(&bottomWidget_);

	connect(&topWidget_, &QListWidget::itemPressed, this, [this](QListWidgetItem* item) {
		if (qApp->mouseButtons() & Qt::RightButton) {
			QList<QListWidgetItem*> items = topWidget_.selectedItems();
			QMenu menu;
			if (items.size() > 1) {
				menu.addAction("Make Group", [items]() {
				});
			}
			menu.exec(QCursor::pos());
		}
	});

	connect(&topWidget_, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
		QString id = item->text();
		if (resManagement_->isGroup(id)) {
			currentCroupId_ = id;
		}
		else {
			currentCroupId_ = "";
		}
	});

	connect(resManagement_, &ResManagement::rollback, this, &ResPanel::reset);

	connect(topWidget_.model(), &QAbstractItemModel::rowsMoved, this, [this](const QModelIndex& parent, int start, int end, const QModelIndex& destination, int row) {
		qDebug() << "move " << start << end << row;
		resManagement_->moveItem(start, end, row);
	});

	reset();
}

void ResPanel::reset() {
	topWidget_.clear();
	bottomWidget_.clear();
	for (auto id : resManagement_->getIdList()) {
		topWidget_.addItem(id);
	}
}