#include "QObjectPanel.h"
#include "PropertyPanel\QPropertyPanel.h"
#include <QBoxLayout>
#include <QEvent>
#include "QObjectEx\QObjectEx.h"
#include "QWidgetEx\Widgets\Buttons\ImageButton.h"
#include "QObjectEx\StaticRegister.h"
#include "ScriptPanel\ScriptPanel.h"

QObjectPanel::QObjectPanel(QObjectEx* object)
	: object_(object)
	, propertyPanel_(new QPropertyPanel(object))
	, scriptPanel_(new ScriptPanel(object))
	, btUndo_(new ImageButton(QPixmap(":/Icons/redo").scaled(QSize(200, 200))))
	, btRedo_(new ImageButton(":/Icons/redo"))
{
	btRedo_->setFixedSize(20, 20);
	btUndo_->setFixedSize(20, 20);

	btUndo_->setToolTip(QObjectEx::undoStack_.undoText());
	btRedo_->setToolTip(QObjectEx::undoStack_.redoText());
	connect(&QObjectEx::undoStack_, &QUndoStack::indexChanged, [this]() {
		btUndo_->setToolTip(QObjectEx::undoStack_.undoText());
		btRedo_->setToolTip(QObjectEx::undoStack_.redoText());
	});

	QHBoxLayout* h = new QHBoxLayout(this);
	h->addWidget(&splitter_);
	h->setContentsMargins(0, 0, 0, 0);
	QWidget* widget = new QWidget;
	QVBoxLayout* v = new QVBoxLayout(widget);
	QHBoxLayout* lh = new QHBoxLayout;
	lh->addWidget(btUndo_);
	lh->addWidget(btRedo_);
	lh->setContentsMargins(0, 0, 0, 0);
	lh->setAlignment(Qt::AlignRight);
	v->addLayout(lh);
	v->addWidget(propertyPanel_);
	v->setContentsMargins(0, 0, 0, 0);
	v->setSpacing(0);
	splitter_.addWidget(widget);
	splitter_.addWidget(scriptPanel_);
	splitter_.setStretchFactor(0, 1);
	splitter_.setStretchFactor(1, 1);
	connect(&splitter_, &QSplitter::splitterMoved, this, [this](int pos, int index) {
		propertyPanelWidth_ = pos;
	});
}

void QObjectPanel::closeEvent(QCloseEvent* event)
{
	Q_EMIT closed();
}

void QObjectPanel::showEvent(QShowEvent* event)
{
	splitter_.setSizes({ int(width() * 0.4),int(width() * 0.6) });
	propertyPanelWidth_ = splitter_.sizes().first();
}

void QObjectPanel::resizeEvent(QResizeEvent* event)
{
	splitter_.setSizes({ propertyPanelWidth_,width() - propertyPanelWidth_ });
}