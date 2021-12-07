#ifndef ColorButton_h__
#define ColorButton_h__

#include <QPushButton>
#include "QTypeEx\QColors.h"
#include "QWidgetEx\Adjuster\Button.h"

class ColorButton : public Button {
public:
	ColorButton(QColor colors);
	void setColor(QColor colors);
protected:
	virtual void flush(QVariant var) override;
	void paintEvent(QPaintEvent* event) override;
private:
	QColor color_;
};

#endif // ColorButton_h__
