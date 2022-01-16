#include "PageArea.h"
#include "QPainter"
#include "QBoxLayout"

PageArea::PageArea()
{
	setLayout(new QVBoxLayout);
	layout()->setAlignment(Qt::AlignTop | Qt::AlignVCenter);
	setWidgetResizable(true);
	setAutoFillBackground(true);
	setStyleSheet(R"(QScrollArea { background: transparent; }
					 QScrollArea > QWidget > QWidget { background: transparent; }
					 QScrollArea > QWidget > QScrollBar { background: palette(base); })");
	setFrameShape(QFrame::NoFrame);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}

