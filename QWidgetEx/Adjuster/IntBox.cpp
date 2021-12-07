#include "IntBox.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMouseEvent>
#include <QLabel>
#include <QDoubleValidator>
#include <QPainter>
#include "QFocusLineEdit.h"
#include "QNeumorphism.h"

IntBox::IntBox(int value/*= 0*/, QString name, QWidget* parent /*= nullptr*/)
    : Adjuster(parent)
    , nameLabel_(new QLabel(name))
    , numberEditer_(new QFocusLineEdit)
    , arrowLabel_(new QLabel)
{
    setFixedHeight(20);
	QNeumorphism* neum = new QNeumorphism;
	neum->setInset(true);
	setGraphicsEffect(neum);

    QHBoxLayout *h = new QHBoxLayout(this);
    h->setContentsMargins(0,0,0,0);
    h->addWidget(nameLabel_);
    h->addWidget(numberEditer_);
    h->addWidget(arrowLabel_);
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
    setNumber(value);
    setEditEnabled(false);
    connect(numberEditer_,&QFocusLineEdit::loseFocus,this,[this](){
        setEditEnabled(false);
    });
    connect(numberEditer_,&QLineEdit::textChanged,this,[this](QString){
        Q_EMIT valueChanged(number());
    });
}

IntBox::~IntBox()
{
}
int IntBox::number()
{
    return numberEditer_->text().toDouble();
}

void IntBox::setNumber(int num){
    numberEditer_->setText(QString::number(num));
}

void IntBox::setEditEnabled(bool enable){
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

bool IntBox::getEditEnabled()
{
    return numberEditer_->focusPolicy() == Qt::FocusPolicy::StrongFocus;
}

void IntBox::moveBox(QPointF offset)
{
    setNumber(number()+ offset.x() * qMax(qAbs(number()/200),1));
}

void IntBox::createPixmap()
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

void IntBox::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton ) {
        clickPosition_ = event->pos();
        if (getEditEnabled()&& arrowLabel_->geometry().contains(event->pos())) {
            setEditEnabled(false);
        }
    }
}

void IntBox::mouseReleaseEvent(QMouseEvent* event)
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

void IntBox::mouseMoveEvent(QMouseEvent* event)
{
	if (!getEditEnabled()) {
        setCursor(Qt::BlankCursor);
        arrowLabel_->setCursor(Qt::CursorShape::BlankCursor);
        QPointF offset = event->position() - clickPosition_;
        moveBox(offset);
        QCursor::setPos(mapToGlobal(clickPosition_.toPoint()));
	}
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
void IntBox::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(rect(),Qt::white);
    QWidget::paintEvent(event);
}

void IntBox::flush(QVariant var)
{
    if (number() != var.toInt()) {
        setNumber(var.toInt());
    }
}

