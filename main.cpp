#include "mainwindow.h"
#include <QApplication>
#include "service.h"
#include "analyser.h"
#include "constantstools.h"
#include <QDebug>
#include "language.h"
#include "logger.h"
#include <QObject>

int main(int argc, char *argv[])
{
    //username: arcsolu
    //password: analyser
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Service *ser = Analyser::getAnalyser();
    Logger infoLogger(QDir().homePath()+"/hello.txt");
    //    infoLogger.info_log("information!");
    //    infoLogger.warning_log("warning");
    //    infoLogger.severe_log("warning");
    //    infoLogger.config_log("warning");
    QObject::connect(&w,SIGNAL(loginSignal()),ser,SLOT(start()));

    ser->start();
    return a.exec();
}
