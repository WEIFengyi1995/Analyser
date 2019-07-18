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
    Logger infoLogger(constantsTools::PATH_REPORT);
    //    infoLogger.info_log("information!");
    //    infoLogger.warning_log("warning");
    //    infoLogger.severe_log("warning");
    //    infoLogger.config_log("warning");
    QObject::connect(&w,SIGNAL(loginSignal()),ser,SLOT(start()));
    QObject::connect(ser,SIGNAL(warning(QString,QString)),&infoLogger,SLOT(warning_log(QString,QString)));
    QObject::connect(ser,SIGNAL(error(QString,QString)),&infoLogger,SLOT(severe_log(QString,QString)));
    QObject::connect(ser,SIGNAL(config(QString,QString)),&infoLogger,SLOT(config_log(QString,QString)));
    QObject::connect(ser,SIGNAL(info(QString,QString)),&infoLogger,SLOT(info_log(QString,QString)));

    ser->start();
    return a.exec();
}
