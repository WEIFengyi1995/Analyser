#include "mainwindow.h"
#include <QApplication>
#include "constantstools.h"
#include <QDebug>
#include "language.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    constantsTools* constTools=new constantsTools();
    language * lang=new language();


    return a.exec();

}
