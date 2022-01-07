#include <QApplication>
#include "Test.h"
#include "QFile"
#include "QObjectEx\StaticRegister.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	Q_INIT_RESOURCE(resources);
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

	panel->show();
	return a.exec();
}

//马爷，我在非工作时间还可以做技术博客吗？就是Vulkan和图形学的一些东西