#ifndef Adjuster_h__
#define Adjuster_h__

#include <QWidget>
#include <QVariant>

class Adjuster :public QWidget {
	Q_OBJECT
public:
	Adjuster(QWidget *parent = nullptr){}
	Q_INVOKABLE virtual void flush(QVariant var){}
Q_SIGNALS:
	void valueChanged(QVariant);
};

#endif // Adjuster_h__
