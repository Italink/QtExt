#include "QRange.h"

QRange::QRange(double lower, double upper, double min, double max)
	: lower_(lower)
	, upper_(upper)
	, min_(min)
	, max_(max)
{
}

void QRange::setLimite(double min, double max)
{
	min_ = min;
	max_ = max;
}

double QRange::min() const
{
	return min_;
}

void QRange::setMin(double min)
{
	min_ = min;
}

double QRange::max() const
{
	return max_;
}

void QRange::setMax(double max)
{
	max_ = max;
}

double QRange::getLower() const
{
	return lower_;
}

void QRange::setLower(double val)
{
	lower_ = val;
}

double QRange::getUpper() const
{
	return upper_;
}

void QRange::setUpper(double val)
{
	upper_ = val;
}

void QRange::setRange(double lower, double upper)
{
	lower_ = lower;
	upper_ = upper;
}

bool QRange::operator==(const QRange& other)
{
	return this->min() == other.min() &&
		this->max() == other.max() &&
		this->getLower() == other.getLower() &&
		this->getUpper() == other.getUpper();
}

QDataStream& operator<<(QDataStream& out, const QRange& var)
{
	out << var.lower_ << var.upper_ << var.min() << var.max();
	return out;
}

QDataStream& operator>>(QDataStream& in, QRange& var)
{
	in >> var.lower_ >> var.upper_ >> var.min_ >> var.max_;
	return in;
}