#include "ImageLoader.h"
#include <QBoxLayout>
#include <QFile>
#include <QFileDialog>
#include <QPushButton>
#include "QNeumorphism.h"
#include "QLabel"

ImageLoader::ImageLoader(QImage value, QWidget* parent /*= nullptr*/)
	: lbDisplay_(new QLabel)
	, btLoad_(new QPushButton("Load"))
{
	lbDisplay_->setFixedSize(60, 60);
	btLoad_->setFixedHeight(60);
	setValue(value);
	setGraphicsEffect(new QNeumorphism);
	QHBoxLayout* h = new QHBoxLayout(this);
	h->setContentsMargins(0, 0, 0, 0);
	h->addWidget(lbDisplay_);
	h->addWidget(btLoad_);
	connect(btLoad_, &QPushButton::clicked, this, &ImageLoader::loadFile);
}

QVariant ImageLoader::getValue()
{
	return data_;
}

void ImageLoader::setValue(QVariant var)
{
	data_ = var.value<QImage>();
	if (data_.isNull())
		return;
	double wh = data_.width() / (double)data_.height();
	if (wh < 1) {
		lbDisplay_->setFixedSize(60 * wh, 60);
	}
	else {
		lbDisplay_->setFixedSize(60, 60 / wh);
	}
	lbDisplay_->setPixmap(QPixmap::fromImage(data_.scaled(lbDisplay_->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
	Q_EMIT valueChanged(data_);
}

void ImageLoader::loadFile()
{
	QString filePath =  QFileDialog::getOpenFileName(nullptr, "Load File");
	if (!QFile::exists(filePath))
		return;
	setValue(QVariant::fromValue(QImage(filePath)));
}

