#ifndef SwitcherAnimBase_h__
#define SwitcherAnimBase_h__
#include <QPainter>
#include "WindowSwitcher.h"

class SwitcherAnimBase {
public:
	virtual void setupLayer(WindowSwitcher::WidgetLayer from, WindowSwitcher::WidgetLayer to);
	virtual void paint(QPainter& painter, qreal process) = 0;
protected:
	WindowSwitcher::WidgetLayer from_;
	WindowSwitcher::WidgetLayer to_;
};

#endif // SwitcherAnimBase_h__
