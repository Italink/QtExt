#ifndef Test_h__
#define Test_h__

#include <QObject>
#include "QTypeEx/QColors.h"
#include "QObjectEx/QObjectEx.h"
#include "QTypeEx/QBoundedDouble.h"
#include "QTypeEx/QBoundedInt.h"

class Test : public QObject {
	Q_OBJECT
public:
	Test();
    IK_AUTO(int,Int) = 1;
    IK_AUTO(float,Float) = 2;
    IK_AUTO(double,Double) = 3;
    IK_AUTO(bool, Bool) = true;
    IK_AUTO(QString,String) = "Hello";
	IK_AUTO(QBoundedDouble, BoundedDouble) = QBoundedDouble(5, 0, 1000);
	IK_AUTO(QBoundedInt, BoundedInt) = QBoundedInt(5, 0, 1000);
	IK_AUTO(QColor, Color) = Qt::red;
	IK_AUTO(QColors, Colors) = { {{0.5,Qt::red},{0.8, Qt::blue}} };

	IK_AUTO(bool, enable_effect) = true;;
	IK_AUTO(bool, inset) = true;;
	IK_AUTO(QBoundedDouble,blur_size)= QBoundedDouble(10,1,40);
	IK_AUTO(QBoundedDouble,distance) =  QBoundedDouble(5,0,100);
	IK_AUTO(QBoundedDouble,angle) =  QBoundedDouble(0,0,360);
	IK_AUTO(QBoundedDouble,strength) = QBoundedDouble(0.8,0,1);

};

#endif // Test_h__
