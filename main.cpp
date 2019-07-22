#include "mainwindow.h"
#include <QApplication>
#include "service.h"
#include "analyser.h"
#include "constantstools.h"
#include <QDebug>
#include "language.h"
#include "logger.h"
<<<<<<< HEAD
#include <QObject>
#include<Qt>
#include"tool.h"
=======
#include "singleinstance.h"

>>>>>>> 5af0df23a78eccf2c04ded3c737649b039cfa1a7
int main(int argc, char *argv[])
{
    //username: arcsolu
    //password: analyser
<<<<<<< HEAD
    QApplication a(argc, argv);
    MainWindow w;
    Logger infoLogger;
    //    Service *ser = Analyser::getAnalyser(infoLogger);
    //    QObject::connect(ser,SIGNAL(finish(QString)),&w,SLOT(done(QString)));
    //    QObject::connect(&w,SIGNAL(loginSignal()),ser,SLOT(start()));
    QString err;
    cutFile(QDir().homePath()+"/test.tt",QDir().homePath()+"/destination.tt",2,3,err);
    //    QObject::connect(ser,SIGNAL(warning(QString,QString)),&infoLogger,SLOT(warning_log(QString,QString)));
    //    QObject::connect(ser,SIGNAL(error(QString,QString)),&infoLogger,SLOT(severe_log(QString,QString)));
    //    QObject::connect(ser,SIGNAL(config(QString,QString)),&infoLogger,SLOT(config_log(QString,QString)));
    //    QObject::connect(ser,SIGNAL(info(QString,QString)),&infoLogger,SLOT(info_log(QString,QString)));
=======
        if(SingleInstance::checkInstance(constantsTools::SERVER_NAME)){
                qDebug()<<"exist";
        }
        else{
            QApplication a(argc, argv);
            MainWindow w;
            SingleInstance instance(w,constantsTools::SERVER_NAME);
            if(instance.listen()){
                Logger infoLogger;
                Service *ser = Analyser::getAnalyser(infoLogger);
                QObject::connect(ser,SIGNAL(finish(QString)),&w,SLOT(done(QString)));
                QObject::connect(&w,SIGNAL(loginSignal()),ser,SLOT(start()));
                QObject::connect(ser,SIGNAL(warning(QString,QString)),&infoLogger,SLOT(warning_log(QString,QString)));
                QObject::connect(ser,SIGNAL(error(QString,QString)),&infoLogger,SLOT(severe_log(QString,QString)));
                QObject::connect(ser,SIGNAL(config(QString,QString)),&infoLogger,SLOT(config_log(QString,QString)));
                QObject::connect(ser,SIGNAL(info(QString,QString)),&infoLogger,SLOT(info_log(QString,QString)));
                w.show();
            }
>>>>>>> 5af0df23a78eccf2c04ded3c737649b039cfa1a7

            return a.exec();
        }

}
