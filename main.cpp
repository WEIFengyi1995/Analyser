#include "mainwindow.h"
#include <QApplication>
#include "service.h"
#include "analyser.h"
#include "constantstools.h"
#include <QDebug>
#include "language.h"

int main(int argc, char *argv[])
{
    //username: arcsolu
    //password: analyser
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Service *ser = Analyser::getAnalyser();
    constantsTools* constTools=new constantsTools();
    language * lang=new language();
    ser->start();
    qDebug()<<constantsTools::PATH_DB;
    qDebug()<<language::info.value("A211");
    //ser->start();
    return a.exec();
}
