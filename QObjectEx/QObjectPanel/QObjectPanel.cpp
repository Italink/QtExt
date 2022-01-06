#include "QObjectPanel.h"
#include "PropertyPanel\QPropertyPanel.h"
#include <QBoxLayout>
#include <QEvent>
#include "CodeEditor\LuaEditor.h"
#include "QObjectEx\QObjectEx.h"

QObjectPanel::QObjectPanel(QObjectEx* object)
	: object_(object)
	, propertyPanel_(new QPropertyPanel(object))
	, codeEditor_(new LuaEditor)
{
	QHBoxLayout* h = new QHBoxLayout(this);
	h->addWidget(&splitter_);
	h->setContentsMargins(0, 0, 0, 0);
	splitter_.addWidget(propertyPanel_);
	splitter_.addWidget(codeEditor_);
	codeEditor_->setFrameShape(QFrame::NoFrame);
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