#include "NumberBox.h"
#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPainter>

NumberBox::NumberBox(double def,int precision,QWidget *parent)
    : QWidget(parent)
    , numberEdit_(new QLineEdit())
    , slider_(new NumberBoxSlider)
    , precision_(precision)
{
    QHBoxLayout *h=new QHBoxLayout(this);
    h->addWidget(numberEdit_);
    h->addWidget(slider_);
    h->setContentsMargins(0,0,0,0);
    numberEdit_->setValidator(new QDoubleValidator);
    numberEdit_->setAlignment(Qt::AlignCenter);
    numberEdit_->setFixedSize(50,20);
    numberEdit_->setFrame(false);
    connect(numberEdit_,&QLineEdit::textChanged,this,[this](){
        Q_EMIT valueChanged(getValue());
    });
    connect(slider_,&NumberBoxSlider::moveSlider,this,[this](qreal offset){
        setValue(getValue()+offset*pow(10,-precision_));
    });
    setValue(def);
}

void NumberBox::setValue(double var)
{
    QString text = QString::number(var, 'f', precision_);
    int index = text.size()-1;
    while (index>0 && text[index] == '0'){
        index--;
    }
    text = text.mid(0,index+1);
    numberEdit_->setText(text);
}

double NumberBox::getValue()
{
    return numberEdit_->text().toDouble();
}

NumberBoxSlider::NumberBoxSlider(){
    setFixedSize(30,16);
    hovered=false;
}

void NumberBoxSlider::enterEvent(QEnterEvent *){
    setCursor(Qt::SplitHCursor);
    hovered=true;
    update();
}

void NumberBoxSlider::leaveEvent(QEvent *){
    setCursor(Qt::ArrowCursor);
    hovered=false;
    update();
}

void NumberBoxSlider::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setBrush(QColor(100,100,100));
    pen.setCapStyle(Qt::RoundCap);
    if(hovered)
        pen.setWidth(3);
    else
        pen.setWidth(2);
    painter.setPen(pen);
    QVector<QPoint> points;
    points<<QPoint(13,2)<<QPoint(5,8)<<QPoint(5,8)<<QPoint(13,14)
          <<QPoint(17,2)<<QPoint(25,8)<<QPoint(25,8)<<QPoint(17,14);
    painter.drawLines(points);
//    painter.fillRect(rect(),Qt::red);
}

void NumberBoxSlider::mousePressEvent(QMouseEvent *event){
    lastPos=event->pos();
    QWidget::mousePressEvent(event);
}

void NumberBoxSlider::mouseMoveEvent(QMouseEvent *e){
    if(e->buttons()&Qt::LeftButton){
        QPoint offset=e->pos()-lastPos;
        emit moveSlider((offset.x()-offset.y()));
    }
    lastPos=e->pos();
}
