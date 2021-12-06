#include "QColors.h"

QColors::QColors()
{
	stops_.push_back({0.5,Qt::white});
}

QColors::QColors(QGradientStops stops)
	:stops_(stops)
{
}



QGradientStops QColors::getStops() const
{
	return stops_;
}

void QColors::setStops(QGradientStops val)
{
	stops_ = val;
}

QDataStream& operator>>(QDataStream& in, QColors& var)
{
	int size;
	in>> size;
	var.stops_.clear();
	qreal key;
	QColor color;
	for (int i = 0; i < size; i++) {
		in>>key>>color;
		var.stops_.push_back({key,color});
	}
	return in;
}

QDataStream& operator<<(QDataStream& out, const QColors& var)
{
	out<<var.stops_.size();
	for (auto& stop : var.stops_) {
		out<<stop.first << stop.second;
	}
	return out;
}

bool QColors::operator==(const QColors& other)
{
	return other.stops_ == this->stops_;
}

