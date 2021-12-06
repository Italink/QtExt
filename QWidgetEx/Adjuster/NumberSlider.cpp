#include "NumberSlider.h"
#include "NumberBox.h"
#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSlider>


NumberSlider::NumberSlider(double number, double min, double max, int precision)
    : min_(min)
    , max_(max)
    , precision_(precision)
    , numberEdit_(new QLineEdit)
    , slider_(new QSlider(Qt::Horizontal))
    , sliderBox_(new NumberBoxSlider)
{
    QHBoxLayout *h=new QHBoxLayout(this);
    h->setContentsMargins(0,0,0,0);
    h->addWidget(numberEdit_);
    h->addWidget(slider_);
    h->addWidget(sliderBox_);
    numberEdit_->setValidator(new QDoubleValidator);
    numberEdit_->setAlignment(Qt::AlignCenter);
    numberEdit_->setFixedSize(40,20);
    numberEdit_->setFrame(false);
    numberEdit_->setText(QString::number(number, 'f', precision_));
    slider_->setMinimumWidth(50);
    slider_->setRange(min*pow(10,precision_),max*pow(10,precision_));

    connect(slider_,&QSlider::valueChanged,this,[this](int value){
        Q_EMIT valueChanged(value);
        numberEdit_->setText(QString::number(value*pow(10,-precision_),'f',precision_));
    });

    connect(numberEdit_,&QLineEdit::editingFinished,this,[this](){
        if(!setValue(numberEdit_->text().toDouble())){
            numberEdit_->setText(QString::number(slider_->value()*pow(10,-precision_),'f',precision_));
        }
    });

    connect(sliderBox_,&NumberBoxSlider::moveSlider,this,[this](qreal offset){
        setValue(getValue()+offset*pow(10,-precision_));
    });
}

bool NumberSlider::setValue(double value)
{
    int tmp=value*pow(10,precision_);
    if(tmp>=slider_->minimum()&&tmp<=slider_->maximum()){
         slider_->setValue(tmp);
         return true;
    }
    return false;
}

double NumberSlider::getValue()
{
    return slider_->value()*pow(10,-precision_);
}
