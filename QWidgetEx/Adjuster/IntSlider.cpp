#include "IntSlider.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>
#include "QFocusLineEdit.h"
#include "QNeumorphism.h"
#include "QValidator"

IntSlider::IntSlider(QBoundedInt number  /*= 0*/, QString name, QWidget* parent /*= nullptr*/)
    : Adjuster(parent)
    , nameLabel_(new QLabel(name))
    , numberEditer_(new QFocusLineEdit)
    , arrowLabel_(new QLabel)
    , value_(number)
{
    setFixedHeight(20);
	QNeumorphism* neum = new QNeumorphism;
	neum->setInset(true);
	setGraphicsEffect(neum);
    QHBoxLayout *h = new QHBoxLayout(this);
    h->setContentsMargins(0,0,0,0);
    h->setSpacing(0);
    h->addWidget(nameLabel_);
    h->addWidget(numberEditer_);
    h->addWidget(arrowLabel_);
    if(nameLabel_->text().isEmpty())
        nameLabel_->setVisible(false);
    nameLabel_->setContentsMargins(0,0,0,2);
    nameLabel_->setAlignment(Qt::AlignCenter);
    nameLabel_->setFixedHeight(height());
    arrowLabel_->setFixedSize(height(),height());
    createPixmap();
    arrowLabel_->setCursor(Qt::CursorShape::SizeHorCursor);
    numberEditer_->setFixedHeight(height());
    numberEditer_->setFrame(QFrame::NoFrame);
    numberEditer_->setValidator(new QIntValidator);
    numberEditer_->setStyleSheet("background-color:transparent;");
    //numberEditer_->setAlignment(Qt::AlignRight);
    setNumber(value_.number());
    setEditEnabled(false);
    connect(numberEditer_,&QFocusLineEdit::loseFocus,this,[this](){
        setEditEnabled(false);
    });
    connect(numberEditer_,&QLineEdit::textChanged,this,[this](QString){
        int num = this->number();
        if (num == value_.number()) {
            return;
        }
        if (value_.setNumber(this->number())) {
            Q_EMIT valueChanged(QVariant::fromValue(value_));
        }
        else {
            setNumber(value_.number());
        }
    });
}

IntSlider::~IntSlider()
{
}

int IntSlider::number()
{
	return numberEditer_->text().toInt();
}

void IntSlider::setNumber(int num){
    numberEditer_->setText(QString::number(num));
}

void IntSlider::setEditEnabled(bool enable){
    if (enable) {
		numberEditer_->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        numberEditer_->setAttribute(Qt::WA_TransparentForMouseEvents,false);
        setCursor(Qt::CursorShape::IBeamCursor);
		numberEditer_ -> activateWindow();
        numberEditer_->setFocus();
        numberEditer_->setReadOnly(false);
        numberEditer_->selectAll();
    }
    else {
		numberEditer_->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        numberEditer_->setAttribute(Qt::WA_TransparentForMouseEvents,true);
		setCursor(Qt::CursorShape::SizeHorCursor);
        numberEditer_->setReadOnly(true);
    }
}

bool IntSlider::getEditEnabled()
{
    return numberEditer_->focusPolicy() == Qt::FocusPolicy::StrongFocus;
}

void IntSlider::moveBox(QPointF offset)
{
    setNumber(number()+ offset.x() * qMax(1,(value_.max() - value_.min())/2000));
}

void IntSlider::createPixmap()
{
	QPixmap image(arrowLabel_->size());
	image.fill(Qt::transparent);
	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setBrush(QColor(100, 100, 100));
	pen.setCapStyle(Qt::RoundCap);
	painter.setPen(pen);
	painter.setBrush(Qt::black);
	QRect rect(0, 0, image.width(), image.height());
	rect.adjust(4, 4, -4, -4);
	QVector<QPoint> points;
	points << rect.topLeft() + QPoint(0, 4) << rect.bottomLeft() << rect.bottomRight() + QPoint(-4, 0);
	painter.drawPolygon(points.data(), points.size());
	points.clear();
	points << rect.topLeft() + QPoint(4, 0) << rect.topRight() << rect.bottomRight() + QPoint(0, -4);
	painter.drawPolygon(points.data(), points.size());
    arrowLabel_->setPixmap(image);
}

void IntSlider::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton ) {
        clickPosition_ = event->pos();
        if (getEditEnabled()&& arrowLabel_->geometry().contains(event->pos())) {
            setEditEnabled(false);
        }
    }
}

void IntSlider::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
        if (this->cursor() == Qt::BlankCursor) {
            setCursor(Qt::CursorShape::SizeHorCursor);
            arrowLabel_->setCursor(Qt::CursorShape::SizeHorCursor);
        }
        else if (clickPosition_ == event->pos() && !getEditEnabled() &&this->cursor()!=Qt::BlankCursor) {
            setEditEnabled(true);
        }
	}
}

void IntSlider::mouseMoveEvent(QMouseEvent* event)
{
	if (!getEditEnabled()) {
        setCursor(Qt::BlankCursor);
        arrowLabel_->setCursor(Qt::CursorShape::BlankCursor);
        QPointF offset = event->position() - clickPosition_;
        moveBox(offset);
        QCursor::setPos(mapToGlobal(clickPosition_.toPoint()));
	}
}

void IntSlider::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.fillRect(rect(), Qt::white);
    QRect slider = numberEditer_->geometry();
    slider.setRight(slider.left()+slider.width()*(value_.number()/double(value_.max()-value_.min())));
    painter.fillRect(slider,QColor(200,200,200));
    QWidget::paintEvent(event);
}

void IntSlider::flush(QVariant var)
{
    int value = var.value<QBoundedInt>().number();
	if (number() != value ) {
		setNumber(value);
	}
}
