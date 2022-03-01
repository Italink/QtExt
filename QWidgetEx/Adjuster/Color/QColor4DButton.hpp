#ifndef QColor4DButton_h__
#define QColor4DButton_h__

#include <QPushButton>
#include "QWidgetEx\Adjuster\Button.h"
#include "QTypeEx\QColor4D.h"

class QColor4DButton : public Button {
public:
	QColor4DButton(QColor4D colors);
	void setColor(QColor4D colors);
	QVariant getValue() override;
	void setValue(QVariant var) override;
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	QColor4D color_;
};

#endif // QColor4DButton_h__