#include "WinCloseButton.h"
#include <QPainter>

WinCloseButton::WinCloseButton()
{

}

void WinCloseButton::paintEvent(QPaintEvent* e)
{
	HoverButton::paintEvent(e);
	QPainter painter(this);
	QPen pen;
	pen.setCapStyle(Qt::RoundCap);
	pen.setWidth(3);
	QRect re = rect().adjusted(8, 8, -8, -8);
	painter.setPen(pen);
	painter.drawLine(re.bottomLeft(), re.topRight());
	painter.drawLine(re.topLeft(), re.bottomRight());
}

