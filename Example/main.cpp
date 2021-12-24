#include <QApplication>
#include "Test.h"
#include "QFile"
#include "QWidgetEx\Window\FramlessWindow.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	Q_INIT_RESOURCE(resources);

	Test test;
	qDebug() << test.dump();

	QObjectPanel* panel = test.createQObjectPane();

	QFile file("save.txt");
	file.open(QFile::ReadOnly);
	test.unserialize(file.readAll());
	file.close();

	QObject::connect(panel, &QObjectPanel::closed, &a, [&]() {
		QFile file("save.txt");
		file.open(QFile::WriteOnly);
		file.write(test.serialize());
		file.close();
	});

	panel->show();
	return a.exec();
}