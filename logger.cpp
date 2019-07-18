#include "logger.h"
#include<QTextStream>
#include<QFile>
#include<QDateTime>
#include<QDebug>
#include<QDir>

Logger::Logger(QString file1)
{
    FileName=file1;
    file=new QFile(file1);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"error while opening "<<FileName;
        return;
    }

}
Logger::~Logger(){
    file->close();
}

void Logger::info(QString action,QString info){
    QTextStream out(file);
    out <<QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [info] "<<action <<" : "<<info;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_INFO<<" [info] "<<COLOR_RESET<<action <<" : "<<info;
}
void Logger::warning(QString action,QString warning){
    QTextStream out(file);
    out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [warning] "<<action <<" : "<<warning;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_WARNNING<<" [warning] "<<COLOR_RESET<<action <<" : "<<warning;
}
void Logger::config(QString action,QString config){
    QTextStream out(file);
    out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [config] "<<action <<" : "<<config;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_CONFIG<<" [config] "<<COLOR_RESET<<action <<" : "<<config;
}
void Logger::severe(QString action,QString severe){
    QTextStream out(file);
    out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [severe] "<<action <<" : "<<severe;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_SEVERE<<" [severe] "<<COLOR_RESET<<action <<" : "<<severe;
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
