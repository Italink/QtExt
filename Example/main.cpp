#include <QApplication>
#include "Test.h"
#include "QFile"
#include "QWidgetEx\Window\FramlessWindow.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	Q_INIT_RESOURCE(resources);
	Test t;
	qDebug() << QObjectEx::dump(&t);
	QFile file("test.txt");
	file.open(QFile::ReadOnly);
	QObjectEx::unserialize(file.readAll(), &t);
	file.close();
	QObjectEx::createQObjectPanel(&t)->show();
	return a.exec();
}