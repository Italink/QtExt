#ifndef DoubleBox_h__
#define DoubleBox_h__

#include "Adjuster.h"

class QFocusLineEdit;
class QLabel;

class DoubleBox : public Adjuster
{
    Q_OBJECT
public:
    DoubleBox(double value = 0,QString name = "", QWidget* parent = nullptr);
    ~DoubleBox();
    double number();
    void setNumber(double num);
    void setEditEnabled(bool enable);
    bool getEditEnabled();
protected:
    void moveBox(QPointF offset);
    void createPixmap();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent* event) override;
    void flush(QVariant var) override;  
private:
    QLabel *nameLabel_;
	QFocusLineEdit* numberEditer_;
    QLabel *arrowLabel_;
	QPointF clickPosition_;
};

#endif // DoubleBox_h__