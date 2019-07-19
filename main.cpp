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
    Service *ser = Analyser::getAnalyser();
    w.show();

    Logger infoLogger;
    infoLogger.setFile(QDir().homePath()+"/hello.txt");
    QObject::connect(&w,SIGNAL(loginSignal()),ser,SLOT(start()),Qt::DirectConnection);
    QObject::connect(ser,SIGNAL(start_Error(QString)),&w,SLOT(done()),Qt::DirectConnection);
    QObject::connect(ser,SIGNAL(warning(QString,QString)),&infoLogger,SLOT(warning_log(QString,QString)),Qt::DirectConnection);
    QObject::connect(ser,SIGNAL(error(QString,QString)),&infoLogger,SLOT(severe_log(QString,QString)),Qt::DirectConnection);
    QObject::connect(ser,SIGNAL(config(QString,QString)),&infoLogger,SLOT(config_log(QString,QString)),Qt::DirectConnection);
    QObject::connect(ser,SIGNAL(info(QString,QString)),&infoLogger,SLOT(info_log(QString,QString)),Qt::DirectConnection);
    return a.exec();
}
