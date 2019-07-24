#include "mainwindow.h"
#include "service.h"
#include "analyser.h"
#include "constantstools.h"
#include "language.h"
#include "logger.h"
#include <QObject>
#include "tool.h"
#include "singleinstance.h"
#include "myapplication.h"


int main(int argc, char *argv[])
{

    //username: arcsolu
    //password: analyser
        if(SingleInstance::checkInstance(constantsTools::SERVER_NAME)){
            return 0;
        }
        else{
                MyApplication a(argc,argv);
                MainWindow w;
                SingleInstance instance(w,constantsTools::SERVER_NAME);
                instance.listen();
                Logger infoLogger;
                Service *ser = Analyser::getAnalyser(infoLogger);
                QObject::connect(ser,SIGNAL(finish(QString)),&w,SLOT(done(QString)),Qt::DirectConnection);
                QObject::connect(&w,SIGNAL(loginSignal()),ser,SLOT(start()));
                QObject::connect(ser,SIGNAL(warning(QString,QString)),&infoLogger,SLOT(warning_log(QString,QString)));
                QObject::connect(ser,SIGNAL(error(QString,QString)),&infoLogger,SLOT(severe_log(QString,QString)));
                QObject::connect(ser,SIGNAL(config(QString,QString)),&infoLogger,SLOT(config_log(QString,QString)));
                QObject::connect(ser,SIGNAL(info(QString,QString)),&infoLogger,SLOT(info_log(QString,QString)));
                QObject::connect(ser,SIGNAL(info(QString,QString)),&w,SLOT(recvInfo(QString,QString)));
                ser->moveToThread(a.getThread());
                infoLogger.moveToThread(a.getThread());
                a.getThread()->start();
                w.show();
                  return a.exec();

    }
}
