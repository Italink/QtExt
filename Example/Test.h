#ifndef Test_h__
#define Test_h__

#include "QObjectEx/QObjectEx.h"
#include "QTypeEx/QBoundedDouble.h"
#include "QTypeEx/QBoundedInt.h"
#include "QTypeEx/QColors.h"
#include "QTypeEx/QCombo.h"

#include <QObject>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include "QTypeEx/QRange.h"

class Test : public QObject {
	Q_OBJECT
public:
	Test();
	Q_AUTO(int, Int) = 1;
	Q_AUTO(float, Float) = 2;
	Q_AUTO(double, Double) = 3;
	Q_AUTO(bool, Bool) = true;
	Q_AUTO(QString, String) = "Hello";
	Q_AUTO(QBoundedDouble, BoundedDouble) = QBoundedDouble(5, 0, 1000);
	Q_AUTO(QBoundedInt, BoundedInt) = QBoundedInt(5, 0, 1000);
	Q_AUTO(QVector2D, Vec2) = QVector2D(1, 2);
	Q_AUTO(QVector3D, Vec3) = QVector3D(1, 2, 3);
	Q_AUTO(QVector4D, Vec4) = QVector4D(1, 2, 3, 4);
	Q_AUTO(QColor, Color) = Qt::red;
	Q_AUTO(QColors, Colors) = { {{0.5,Qt::red},{0.8, Qt::blue}} };
	Q_AUTO(QCombo, Combo) = { 1,{"A","B","C"} };
	Q_AUTO(QRange, Range) = QRange(50, 100, 0, 200);
	enum MCustomEnum {
		Left = 1, Right, Top, Bottom
	};
	Q_ENUM(MCustomEnum);

	Q_AUTO(MCustomEnum, CustomEnum) = Right;

	Q_AUTO(bool, enable_effect) = true;;
	Q_AUTO(bool, inset) = true;;
	Q_AUTO(QBoundedDouble, blur_size) = QBoundedDouble(10, 1, 40);
	Q_AUTO(QBoundedDouble, distance) = QBoundedDouble(5, 0, 100);
	Q_AUTO(QBoundedDouble, angle) = QBoundedDouble(0, 0, 360);
	Q_AUTO(QBoundedDouble, strength) = QBoundedDouble(0.8, 0, 1);
};

#endif // Test_h__
