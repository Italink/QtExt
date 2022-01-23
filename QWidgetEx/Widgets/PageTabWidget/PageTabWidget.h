#ifndef PageTabWidget_h__
#define PageTabWidget_h__

#include "QTabWidget"
#include "QVariantAnimation"

class PageTabWidget : public QTabWidget {
public:
	PageTabWidget();
	void addPage(QString text,QIcon icon, QWidget* page);
protected:
	double process_ = 1;
	QVariantAnimation switchAnim_;
	void paintEvent(QPaintEvent*) override;
};

#endif // PageTabWidget_h__
