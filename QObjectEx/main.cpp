#include <QApplication>
#include "Binds\BindAdjuster.h"
#include "Test.h"
#include "QObjectEx.h"
#include "QFile"
#include "QWidgetEx\Window\FramlessWindow.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Test t;
    qDebug()<<QObjectEx::dump(&t);
    QFile file("test.txt");
    file.open(QFile::WriteOnly);
    file.write( QObjectEx::dump(&t));
    file.close();
    FramelessWidget w("s");
    w.show();
    QObjectEx::createQObjectPanel(&t)->show();
    return a.exec();
}
