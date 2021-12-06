#include "QSliderNumber.h"

QSliderNumber::QSliderNumber(double number, double min, double max, int precision /*= 0*/) : number_(number)
, min_(min)
, max_(max)
, precision_(precision)
{

}

void QSliderNumber::setRange(double min, double max)
{
	min_ = min;
	max_ = max;
}

double QSliderNumber::min() const
{
	return min_;
}

void QSliderNumber::setMin(double min)
{
	min_ = min;
}

double QSliderNumber::max() const
{
	return max_;
}

void QSliderNumber::setMax(double max)
{
	max_ = max;
}

int QSliderNumber::precision() const
{
	return precision_;
}

void QSliderNumber::setPrecision(int precision)
{
	precision_ = precision;
}

double QSliderNumber::number() const
{
	return number_;
}

bool QSliderNumber::setNumber(double number)
{
	if (number == number_ || number <min_ || number > max_)
		return false;
	number_ = number;
	return true;
}

bool QSliderNumber::operator==(const QSliderNumber& other)
{
	return this->number() == other.number();
}

QDataStream& operator<<(QDataStream& out, const QSliderNumber& var)
{
	out<<var.number()<<var.min()<<var.max()<<var.precision();
	return out;
}

QDataStream& operator>>(QDataStream& in, QSliderNumber& var)
{
	in >> var.number_ >> var.min_ >> var.max_ >> var.precision_;
	return in;
}
