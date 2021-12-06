#ifndef QSliderNumber_h__
#define QSliderNumber_h__

#include <QMetaType>

class QSliderNumber{

public:
	QSliderNumber() {};
	QSliderNumber(double number, double min, double max, int precision = 0);

	void setRange(double min, double max);

	double min() const;

	void setMin(double min);

	double max() const;
	void setMax(double max);

	int precision() const;
	void setPrecision(int precision);

	double number() const;

	bool setNumber(double number);

	bool operator==(const QSliderNumber& other);

	friend QDataStream& operator<<(QDataStream& out, const QSliderNumber& var);
	friend QDataStream& operator>>(QDataStream& in, QSliderNumber& var);

private:
	double number_ = 0;
	double min_ = 0, max_ = 100;
	int precision_ = 0;

};


Q_DECLARE_BUILTIN_METATYPE(QSliderNumber, 201, QSliderNumber);

#endif // QSliderNumber_h__