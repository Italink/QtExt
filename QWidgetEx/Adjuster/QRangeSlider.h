#ifndef QRangeSlider_h__
#define QRangeSlider_h__

#include "Adjuster.h"
#include "QTypeEx/QBoundedDouble.h"
#include "QTypeEx/QRange.h"

class QFocusLineEdit;
class QLabel;
class CustomSlider;

class QRangeSlider : public Adjuster
{
	Q_OBJECT
public:
	QRangeSlider(QRange range, QWidget* parent = nullptr);
	~QRangeSlider();
	QVariant getValue() override;
	void setValue(QVariant var) override;
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	QRange range_;
	QFocusLineEdit* lowerEditer_;
	CustomSlider* slider_;
	QFocusLineEdit* upperEditer_;
};

#endif // QRangeSlider_h__
