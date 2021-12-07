#ifndef ColorsButton_h__
#define ColorsButton_h__

#include <QPushButton>
#include "QTypeEx\QColors.h"
#include "QWidgetEx\Adjuster\Button.h"


class ColorsButton : public Button{
public:
	ColorsButton(QColors colors);
	void setColors(QColors colors);
protected:
	virtual void flush(QVariant var) override;
	void paintEvent(QPaintEvent* event) override;
private:
	QColors colors_;
};

#endif // ColorsButton_h__
