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
	v->setContentsMargins(2, 2, 2, 2);
	v->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	v->addWidget(&topWidget_);
	v->addWidget(&bottomWidget_);
	bottomWidget_.setVisible(false);
	connect(&topWidget_, &QListWidget::itemPressed, this, [this](QListWidgetItem* item) {
		if (qApp->mouseButtons() & Qt::RightButton) {
			QList<QListWidgetItem*> items = topWidget_.selectedItems();
			QStringList idList;
			for (auto& item : items) {
				idList << item->text();
			}
			QMenu menu;
			if (items.size() > 1) {
				menu.addAction("Make Group", [idList,this]() {
					resManagement_->makeGroup(idList);
				});
			}
			else if (items.size() == 1) {
				if (resManagement_->isGroup(idList.first())) {
					menu.addAction("Take Apart ", [idList, this]() {
						resManagement_->takeApart(idList.first());
					});
				}
			}
			menu.exec(QCursor::pos());
		}
	});

	connect(&topWidget_, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
		QString id = item->text();
		setTopCurrent(id);
	});

	connect(&topWidget_, &ResListWidget::dropItems, this, [this](int dstIndex, QList<QListWidgetItem*> items) {
		QStringList idList;
		for (auto& item : items) {
			idList << item->text();

		}
	});

	connect(&bottomWidget_, &ResListWidget::dropItems, this, [this](int dstIndex, QList<QListWidgetItem*> items) {
		QStringList idList;
		for (auto& item : items) {
			idList << item->text();
			if (item->text() == currentGroupId_) {
				reset();
				return;
			}
		}
		resManagement_->enterGroup(currentGroupId_, idList, dstIndex);
	});

	connect(&topWidget_, &ResListWidget::dropItems, this, [this](int dstIndex, QList<QListWidgetItem*> items) {
		QStringList idList;
		for (auto& item : items) {
			idList << item->text();
		}
		resManagement_->leaveGroup(currentGroupId_, idList, dstIndex);
	});

	connect(resManagement_, &ResManagement::rollback, this, &ResPanel::reset);

	connect(topWidget_.model(), &QAbstractItemModel::rowsMoved, this, [this](const QModelIndex& parent, int start, int end, const QModelIndex& destination, int row) {
		resManagement_->moveItem(start, end, row);
	});

	connect(bottomWidget_.model(), &QAbstractItemModel::rowsMoved, this, [this](const QModelIndex& parent, int start, int end, const QModelIndex& destination, int row) {
		resManagement_->moveGroupChildItem(currentGroupId_,start, end, row);
	});

	reset();
}

void ResPanel::reset() {
	topWidget_.clear();
	bottomWidget_.clear();
	for (auto id : resManagement_->getIdList()) {
		topWidget_.addItem(id);
	}
	if (!currentGroupId_.isEmpty()) {
		setTopCurrent(currentGroupId_);
	}
	if (!currentSingleId_.isEmpty()) {
		setTopCurrent(currentSingleId_);
	}
}

void ResPanel::setTopCurrent(QString id)
{
	if (resManagement_->isGroup(id)) {
		bottomWidget_.show();
		bottomWidget_.clear();
		currentGroupId_ = id;
		currentSingleId_ = "";
		for (auto& childId : resManagement_->getChildIdList(id)) {
			bottomWidget_.addItem(childId);
		}

		/*for (int i = 0; i < topWidget_.count(); i++) {
			QListWidgetItem* item = topWidget_.item(i);
			if (item->text() == currentGroupId_) {
				topWidget_.setCurrentRow(0);
			}
		}*/
	}
	else {
		currentGroupId_ = "";
		bottomWidget_.hide();
		currentSingleId_ = id;
		//for (int i = 0; i < topWidget_.count(); i++) {
		//	QListWidgetItem* item = topWidget_.item(i);
		//	if (item->text() == currentSingleId_ && !item->isSelected()) {
		//		item->setSelected(true);
		//	}
		//}
	}
}

