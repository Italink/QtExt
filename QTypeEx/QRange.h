#ifndef QRange_h__
#define QRange_h__

#include <QMetaType>

class QRange {
public:
	QRange() {};
	QRange(double lower, double upper, double min, double max);

	void setLimite(double min, double max);
	double min() const;
	void setMin(double min);
	double max() const;
	void setMax(double max);

	double getLower() const;
	void setLower(double val);
	double getUpper() const;
	void setUpper(double val);
	void setRange(double lower, double upper);

	bool operator==(const QRange& other);

	friend QDataStream& operator<<(QDataStream& out, const QRange& var);
	friend QDataStream& operator>>(QDataStream& in, QRange& var);

private:
	double lower_ = 0;
	double upper_ = 100;
	double min_ = 0, max_ = 100;
};

Q_DECLARE_METATYPE(QRange)

#endif // QRange_h__
