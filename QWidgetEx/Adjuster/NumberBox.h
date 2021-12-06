#ifndef NUMBERBOX_H
#define NUMBERBOX_H

#include <QWidget>

class QLineEdit;
class NumberBoxSlider;

class NumberBox : public QWidget
{
    Q_OBJECT
public:
    explicit NumberBox(double def,int precision = 3, QWidget *parent = nullptr);
    void setValue(double var);
    double getValue();
private:
    QLineEdit *numberEdit_;
    NumberBoxSlider *slider_;
    int precision_;
signals:
    void valueChanged(double);
};

class NumberBoxSlider : public QWidget{
    Q_OBJECT
public:
    NumberBoxSlider();
protected:
    virtual void enterEvent(QEnterEvent *) override;
    virtual void leaveEvent(QEvent *) override;
    virtual void paintEvent(QPaintEvent *) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
signals:
    void moveSlider(qreal);
private:
    bool hovered;
    QPoint lastPos;
};


#endif // NUMBERBOX_H
