#include "QCombo.h"
#include <QDataStream>

QCombo::QCombo(int currentIndex, QStringList items)
	: currentIndex_(currentIndex)
	, items_(items)
{
}

QCombo::QCombo()
{
}

QCombo::QCombo(QString currentItem, QStringList items)
	:currentIndex_(items.indexOf(currentItem))
	, items_(items)
{
}

bool QCombo::operator==(const QCombo& other)
{
	return currentIndex_ == other.currentIndex_ && items_ == other.items_;
}

QDataStream& operator>>(QDataStream& in, QCombo& var)
{
	in >> var.currentIndex_ >> var.items_;
	return in;
}
QDataStream& operator<<(QDataStream& out, const QCombo& var)
{
	out << var.currentIndex_ << var.items_;
	return out;
}