#include "mainwindow.h"
#include <QApplication>
#include "service.h"
#include "analyser.h"
#include "constantstools.h"
#include <QDebug>
#include "language.h"
#include "logger.h"
#include <QObject>
#include<Qt>
int main(int argc, char *argv[])
{
    //username: arcsolu
    //password: analyser
    QApplication a(argc, argv);
    MainWindow w;
    Logger infoLogger;
    Service *ser = Analyser::getAnalyser(infoLogger);
    QObject::connect(ser,SIGNAL(finish(QString)),&w,SLOT(done(QString)));
    QObject::connect(&w,SIGNAL(loginSignal()),ser,SLOT(start()));

    QObject::connect(ser,SIGNAL(warning(QString,QString)),&infoLogger,SLOT(warning_log(QString,QString)));
    QObject::connect(ser,SIGNAL(error(QString,QString)),&infoLogger,SLOT(severe_log(QString,QString)));
    QObject::connect(ser,SIGNAL(config(QString,QString)),&infoLogger,SLOT(config_log(QString,QString)));
    QObject::connect(ser,SIGNAL(info(QString,QString)),&infoLogger,SLOT(info_log(QString,QString)));
    QObject::connect(ser,SIGNAL(info(QString,QString)),&w,SLOT(recvInfo(QString,QString)));
    QObject::connect(ser,SIGNAL(warning(QString,QString)),&w,SLOT(recvInfo(QString,QString)));
    QObject::connect(ser,SIGNAL(error(QString,QString)),&w,SLOT(recvInfo(QString,QString)));
    QObject::connect(ser,SIGNAL(config(QString,QString)),&w,SLOT(recvInfo(QString,QString)));
    w.show();


    return a.exec();
}
