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
    qDebug()<<"";

    //ser->start();

    return a.exec();
}
