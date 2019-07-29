#include "mainwindow.h"
#include "service.h"
#include "analyser.h"
#include "constantstools.h"
#include "language.h"
#include "logger.h"
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
//        qDebug()<<"   gfix -user "+ DBConnector::ISC_USER+" -password "+
//                  DBConnector::ISC_PASSWORD+" -v -full "+ constantsTools::FILE_DB_AUDIT<<
//                  constantsTools::FILE_GFIX;
        instance.listen();
        Logger infoLogger;
        Service *ser = Analyser::getAnalyser(infoLogger);
        QObject::connect(ser,SIGNAL(finish(QString)),&w,SLOT(done(QString)));
        QObject::connect(&w,SIGNAL(loginSignal()),ser,SLOT(start()));
        QObject::connect(ser,SIGNAL(warning(QString,QString)),&infoLogger,SLOT(warning_log(QString,QString)));
        QObject::connect(ser,SIGNAL(error(QString,QString)),&infoLogger,SLOT(severe_log(QString,QString)));
        QObject::connect(ser,SIGNAL(config(QString,QString)),&infoLogger,SLOT(config_log(QString,QString)));
        QObject::connect(ser,SIGNAL(info(QString,QString)),&infoLogger,SLOT(info_log(QString,QString)));
        QObject::connect(ser,SIGNAL(info(QString,QString)),&w,SLOT(recvInfo(QString,QString)));
        QObject::connect(ser,SIGNAL(processBar(int)),&w,SLOT(NmonProcess(int)));
        ser->moveToThread(a.getThread());
        infoLogger.moveToThread(a.getThread());
        a.getThread()->start();
        w.show();
        return a.exec();
    }
}
