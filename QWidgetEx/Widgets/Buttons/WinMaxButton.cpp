#include <QPainter>
#include "WinMaxButton.h"

WinMaxButton::WinMaxButton()
{
	hoverColor = Qt::red;
}

void WinMaxButton::paintEvent(QPaintEvent* e) {
	HoverButton::paintEvent(e);
	QPainter painter(this);
	QPen pen;
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	painter.setRenderHint(QPainter::Antialiasing);
	pen.setWidth(3);
	painter.setPen(pen);
	painter.drawRect(rect().adjusted(8, 8, -8, -8));
}

