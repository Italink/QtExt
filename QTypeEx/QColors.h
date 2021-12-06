#ifndef QColors_h__
#define QColors_h__

#include <QBrush>
#include <QMetaType>

class QColors{
public:
	QColors();
	QColors(QGradientStops stops);
	QGradientStops getStops() const;
	void setStops(QGradientStops val);
	bool operator==(const QColors& other);

	friend QDataStream& operator<<(QDataStream& out, const QColors& var);
	friend QDataStream& operator>>(QDataStream& in, QColors& var);
private:
	QGradientStops stops_;
};
Q_DECLARE_BUILTIN_METATYPE(QColors,200,QColors);

#endif // QColors_h__
