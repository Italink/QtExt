#ifndef QIntBox_h__
#define QIntBox_h__

#include "Adjuster.h"

class QFocusLineEdit;
class QLabel;

class IntBox : public Adjuster
{
    Q_OBJECT
public:
    IntBox(int value = 0,QString name = "", QWidget* parent = nullptr);
    ~IntBox();
    int number();
    void setNumber(int num);
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

#endif // QIntBox_h__
