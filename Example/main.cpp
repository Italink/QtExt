#include <QApplication>
#include "Test.h"
#include "QFile"
#include "QWidgetEx\Window\FramlessWindow.h"
#include "QJsonDocument"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Test t;
    qDebug()<<QObjectEx::dump(&t);
	QFile file("test.txt");
	file.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();
    QObjectEx::fromJson(doc.object(),&t);
    QObjectEx::createQObjectPanel(&t)->show();
    return a.exec();
}
