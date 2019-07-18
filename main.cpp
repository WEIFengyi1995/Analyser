#include "mainwindow.h"
#include <QApplication>
#include "service.h"
#include "analyser.h"
#include "constantstools.h"
#include <QDebug>
#include "language.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    //username: arcsolu
    //password: analyser
    QApplication a(argc, argv);
    MainWindow w;
    Service *ser = Analyser::getAnalyser();
    QObject::connect(&w,SIGNAL(loginSignal()),ser,SLOT(start()));
    w.show();
    return a.exec();
}
