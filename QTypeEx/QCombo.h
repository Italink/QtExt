#ifndef QCombo_h__
#define QCombo_h__

#include <QStringList>
#include <QMetaType>

class QCombo {
public:
	QCombo();
	QCombo(int currentIndex, QStringList items);
	QCombo(QString currentItem, QStringList items);
	bool operator==(const QCombo& other);
	friend QDataStream& operator<<(QDataStream& out, const QCombo& var);
	friend QDataStream& operator>>(QDataStream& in, QCombo& var);
public:
	int currentIndex_ = 0;
	QStringList items_ = {};
};

Q_DECLARE_METATYPE(QCombo);

#endif // QCombo_h__