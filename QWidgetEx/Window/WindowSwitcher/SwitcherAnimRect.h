#ifndef SwitcherAnimRect_h__
#define SwitcherAnimRect_h__
#include "SwitcherAnimBase.h"

class SwitcherAnimRect :public SwitcherAnimBase {
public:
	virtual void setupLayer(WindowSwitcher::WidgetLayer from, WindowSwitcher::WidgetLayer to) override;
	void paint(QPainter& painter, qreal process) override;
private:
	QList<QList<QPair<QRect, QRect>>> stages;
};

#endif // SwitcherAnimRect_h__
