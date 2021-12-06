#ifndef Test_h__
#define Test_h__

#include <QObject>
#include "QTypeEx/QSliderNumber.h"
#include "QTypeEx/QColors.h"
#include "QObjectEx/QObjectEx.h"

class Test : public QObject {
	Q_OBJECT
public:
    IK_AUTO(int,Int) = 1;
    IK_AUTO(float,Float) = 2;
    IK_AUTO(double,Double) = 3;
    IK_AUTO(bool, Bool) = true;
    IK_AUTO(QString,String) = "Hello";
	IK_AUTO(QSliderNumber, SliderNumber) = QSliderNumber(5, 0, 1000, 1);
	IK_AUTO(QColor, Color) = Qt::red;
	IK_AUTO(QColors, Colors) = { {{0.5,Qt::red},{0.8, Qt::blue}} };
};

#endif // Test_h__
