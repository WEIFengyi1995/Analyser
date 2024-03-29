#include "logger.h"
#include<QTextStream>
#include<QFile>
#include<QDateTime>
#include<QDebug>
#include<QDir>

Logger::Logger()
{
    file=nullptr;
}

void Logger::setFile(QString file1){
    if(file!=nullptr&&file->isOpen()){
        file->close();
    }
    FileName = file1;
    file = new QFile(file1);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"error while opening "<<file1<<file->errorString();
        return;
    }
}
Logger::~Logger(){
    if(file != nullptr){
        file->close();
    }

}

void Logger::info(QString action,QString info){
    if(!file->isOpen()){
        qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_SEVERE<<" [severe] "<<COLOR_RESET<< "log file not found ";
        emit error("file not open!");
    }else{
        QTextStream out(file);
        if(!action.isEmpty()){
            out<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [info] "<<action <<" : "<<info<<"\n";
            qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_INFO<<" [info] "<<COLOR_RESET<<action <<" : "<<info<<"\n";
        }else{
            out<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [info] " <<" : "<<info<<"\n";
            qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_INFO<<" [info] "<<COLOR_RESET <<" : "<<info<<"\n";
        }
    }
}

void Logger::warning(QString action,QString warning){
    if(!file->isOpen()){
        qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_SEVERE<<" [severe] "<<COLOR_RESET<< "log file not found ";
        emit error("file not open!");
    }else{
        QTextStream out(file);
        if(!action.isEmpty()){
            out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [warning] "<<action <<" : "<<warning<<"\n";
            qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_WARNNING<<" [warning] "<<COLOR_RESET<<action <<" : "<<warning<<"\n";
        }
        else{
            out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [warning] " <<" : "<<warning<<"\n";
            qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_WARNNING<<" [warning] "<<COLOR_RESET <<" : "<<warning<<"\n";

        }
    }
}

void Logger::config(QString action,QString config){
    if(!file->isOpen()){
        qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_SEVERE<<" [severe] "<<COLOR_RESET<< "log file not found ";
        emit error("file not open!");}
    else{
        QTextStream out(file);
        if(!action.isEmpty()){
            out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [config] "<<action <<" : "<<config<<"\n";
            qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_CONFIG<<" [config] "<<COLOR_RESET<<action <<" : "<<config<<"\n";
        }else{
            out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [config] " <<" : "<<config<<"\n";
            qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_CONFIG<<" [config] "<<COLOR_RESET <<" : "<<config<<"\n";

        }
    }
}

void Logger::severe(QString action,QString severe){
    if(!file->isOpen()){
        qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_SEVERE<<" [severe] "<<COLOR_RESET<< "log file not found ";
        emit error("file not open!");}
    else{
        QTextStream out(file);
        if(!action.isEmpty()){
            out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [severe] "<<action <<" : "<<severe<<"\n";
            qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_SEVERE<<" [severe] "<<COLOR_RESET<<action <<" : "<<severe<<"\n";
        }else{
            out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [severe] "<<" : "<<severe<<"\n";
            qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_SEVERE<<" [severe] "<<COLOR_RESET <<" : "<<severe<<"\n";
        }
    }
}

    void Logger::info_log(QString action,QString information){
        this->info(action,information);
    }

    void Logger::config_log(QString action,QString config){
        this->config(action,config);
    }
    void Logger::warning_log(QString action,QString war){
        this->warning(action,war);
    }
    void Logger::severe_log(QString action,QString sev){
        this->severe(action,sev);
    }
