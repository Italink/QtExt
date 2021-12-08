#include "WindowSwitcher.h"
#include <QApplication>
#include <QScreen>
#include <QPainter>
#include "SwitcherAnimRect.h"

WindowSwitcher::WindowSwitcher()
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_TransparentForMouseEvents);
	setGeometry(QApplication::primaryScreen()->geometry());
	switchAnim_.setDuration(500);
	switchAnim_.setStartValue(0.0);
	switchAnim_.setEndValue(1.0);
	widgetStack_.push_back({ this });
	animPainters[SwitcherAnimType::Rect] = new SwitcherAnimRect;
}

void WindowSwitcher::turnTo(QWidget* widget, bool createNewLayer, bool clearChildren, bool alignRightTop /*= false*/)
{
	Q_ASSERT(widget != nullptr);
	WidgetLayer layer;
	layer.root = widget;
	widget->show();
	widget->setVisible(false);
	widget->installEventFilter(this);
	if (!widgetStack_.isEmpty()) {
		QWidget* current = widgetStack_.back().root;
		if (current != nullptr) {
			current->hide();
			if (alignRightTop) {
				QRect rect = widget->geometry();
				rect.moveTopRight(current->geometry().topRight());
				widget->setGeometry(rect);
			}
			for (auto& child : widgetStack_.back().children) {
				child->hide();
			}
		}
	}
	playAnim(widgetStack_.back(), layer);
	if (clearChildren)
		widgetStack_.back().children.clear();
	if (createNewLayer)
		widgetStack_.push_back(layer);
}

void WindowSwitcher::popLayer() {
	if (widgetStack_.size() <= 1)
		return;
	WidgetLayer layer = widgetStack_.back();
	widgetStack_.pop_back();
	playAnim(layer, widgetStack_.back());
}

void WindowSwitcher::splitTo(QWidget* widget)
{
	Q_ASSERT(widget != nullptr && !widgetStack_.isEmpty());
	WidgetLayer layer = widgetStack_.back();
	widget->show();
	widget->setVisible(false);
	widget->installEventFilter(this);
	layer.children.push_back(widget);
	playAnim(widgetStack_.back(), layer);
	widgetStack_.back() = layer;
}

void WindowSwitcher::setAnimDuration(int ms)
{
	switchAnim_.setDuration(ms);
}

void WindowSwitcher::playAnim(WidgetLayer from, WidgetLayer to)
{
	show();
	switchAnim_.start();
	currentState_ = { from,to,0 };
	getCurrentAnim()->setupLayer(from, to);
	connect(&switchAnim_, &QVariantAnimation::valueChanged, this, [this](QVariant var) {
		currentState_.process = var.toDouble();
		update();
		});
	connect(&switchAnim_, &QPropertyAnimation::finished, this, [this, from, to]() {
		if (to.root != nullptr) {
			to.root->show();
			to.root->setVisible(true);
			for (auto it : to.children) {
				it->show();
				it->setVisible(true);
			}
			to.root->activateWindow();
			to.root->setFocus();
		}
		switchAnim_.disconnect();
		currentState_.process = -1;
		hide();
		});
}

SwitcherAnimBase* WindowSwitcher::getCurrentAnim()
{
	return animPainters[currentAnimType_];
}

void WindowSwitcher::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	if (currentState_.process >= 0)
		getCurrentAnim()->paint(painter, currentState_.process);
}

bool WindowSwitcher::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::Close && widgetStack_.size() > 1) {
		if (watched == widgetStack_.back().root) {
			popLayer();
		}
		else if (widgetStack_.back().children.contains(watched)) {
			widgetStack_.back().children.removeOne(watched);
		}
		watched->removeEventFilter(this);
	}
	return QObject::eventFilter(watched, event);
}