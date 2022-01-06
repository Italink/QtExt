#include <QApplication>
#include "Test.h"
#include "QFile"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	Q_INIT_RESOURCE(resources);
	qRegisterMetaType<Test>("Test");

	QFile file("save.txt");
	file.open(QFile::ReadOnly);
	QObjectEx* test = QObjectEx::createFromData(file.readAll());	//���ļ��ж�ȡ���ݲ���������
	file.close();
	if (test == nullptr)
		test = new Test;

	QObjectPanel* panel = test->createQObjectPanel();				//�����������
	panel->show();

	QObject::connect(panel, &QObjectPanel::closed, &a, [&]() {		//�ر����ʱ�������
		QFile file("save.txt");
		file.open(QFile::WriteOnly);
		file.write(test->serialize());
		file.close();
	});

	panel->show();
	return a.exec();
}