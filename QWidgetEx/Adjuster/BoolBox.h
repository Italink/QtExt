#ifndef BoolBox_h__
#define BoolBox_h__

#include "Button.h"

class BoolBox : public Button
{
	Q_OBJECT
public:
	BoolBox(bool value = 0, QWidget* parent = nullptr);
	void setChecked(bool value);
protected:
	void paintEvent(QPaintEvent* event) override;
	void flush(QVariant var) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
protected:
	QPoint clickPosition_;
	bool checked_;
};

#endif // BoolBox_h__
