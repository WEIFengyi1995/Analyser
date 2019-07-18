//#include "mainwindow.h"
#include <QApplication>
#include "constantstools.h"
#include <QDebug>
#include <QtMath>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
    constantsTools* b=new constantsTools();
    qDebug()<<b->PATH_DB<<"path_db";
    return 0;

}
