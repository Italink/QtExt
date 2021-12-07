#include "QBoundedDouble.h"
#include <QDebug>
QBoundedDouble::QBoundedDouble(double number, double min, double max) : value_(number)
, min_(min)
, max_(max)
{

}

void QBoundedDouble::setRange(double min, double max)
{
	min_ = min;
	max_ = max;
}

double QBoundedDouble::min() const
{
	return min_;
}

void QBoundedDouble::setMin(double min)
{
	min_ = min;
}

double QBoundedDouble::max() const
{
	return max_;
}

void QBoundedDouble::setMax(double max)
{
	max_ = max;
}


double QBoundedDouble::number() const
{
	return value_;
}

bool QBoundedDouble::setNumber(double number)
{
	number = qBound(min_, number, max_);
	if (number == value_)
		return false;
	value_ = number;
	return true;
}

bool QBoundedDouble::operator==(const QBoundedDouble& other)
{
	return this->number() == other.number();
}

QDataStream& operator<<(QDataStream& out, const QBoundedDouble& var)
{
	out<<var.number()<<var.min()<<var.max();
	return out;
}

QDataStream& operator>>(QDataStream& in, QBoundedDouble& var)
{
	in >> var.value_ >> var.min_ >> var.max_ ;
	return in;
}
