#ifndef NUMBERSLIDER_H
#define NUMBERSLIDER_H

#include <QWidget>
class QLineEdit;
class QSlider;
class NumberBoxSlider;

class NumberSlider : public QWidget
{
    Q_OBJECT
public:
    explicit NumberSlider(double number,double min,double max,int precision = 0);
    bool setValue(double value);
    double getValue();
private:
    double min_,max_;
    int precision_;
    QLineEdit *numberEdit_;
    QSlider *slider_;
    NumberBoxSlider *sliderBox_;
signals:
    void valueChanged(double);
};

#endif // NUMBERSLIDER_H
