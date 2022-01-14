#include <QApplication>
#include "Test.h"
#include "QFile"
#include "QWidgetEx\Window\FramlessWindow.h"
#include "QWidgetEx\Application\DesktopApplication.h"
#include "QWidgetEx\Window\WallpaperWindow.h"
#include "QWidgetEx\Widgets\ResPanel\ResPanel.h"
#include <QUndoView>

int main(int argc, char* argv[]) {
	Q_INIT_RESOURCE(resources);
	DesktopApplication a(":/Icons/redo", argc, argv);
	qRegisterMetaType<Test>("Test");

	QFile file("save.txt");
	file.open(QFile::ReadOnly);
	QObjectEx* test = QObjectEx::createFromData(file.readAll());	//从文件中读取数据并创建对象
	file.close();
	if (test == nullptr)
		test = new Test;

	QObjectPanel* panel = test->createQObjectPanel();				//创建对象面版
	panel->show();

	QObject::connect(panel, &QObjectPanel::closed, &a, [&]() {		//关闭面板时保存对象
		QFile file("save.txt");
		file.open(QFile::WriteOnly);
		file.write(test->serialize());
		file.close();
		test->dump();
	});
	QColor color = Qt::red;
	qDebug() << color;
	QUndoView view(&QObjectEx::undoStack_);
	view.show();

	//FramelessWidget frameLess("hello");
	//frameLess.show();
	panel->show();

	//ResPanel res;
	//res.show();

	return a.exec();
}