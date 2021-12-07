#ifndef LineEdit_h__
#define LineEdit_h__


#include "QWidgetEx/Adjuster/Adjuster.h"
class QFocusLineEdit;

class LineEdit : public Adjuster
{
	Q_OBJECT
public:
	LineEdit(QString str);

    void flush(QVariant var) override;
private:
	QFocusLineEdit *lineEdit_;
};


#endif // LineEdit_h__
