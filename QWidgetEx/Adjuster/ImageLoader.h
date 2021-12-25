#ifndef ImageLoader_h__
#define ImageLoader_h__

#include "Adjuster.h"
#include <QImage>

class QPushButton;
class QLabel;
class ImageLoader : public Adjuster
{
	Q_OBJECT
public:
	ImageLoader(QImage value, QWidget* parent = nullptr);
	QVariant getValue() override;
	void setValue(QVariant var) override;
protected:
	void loadFile();
	QImage data_;
	QLabel* lbDisplay_;
	QPushButton* btLoad_;
};

#endif // ImageLoader_h__

