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

void Logger::info(QString info){
    QTextStream out(file);
    out <<QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [info] "<<info;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_INFO<<" [info] "<<COLOR_RESET<<info;
}
void Logger::warning(QString warning){
    QTextStream out(file);
    out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [warning] "<<warning;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_WARNNING<<" [warning] "<<COLOR_RESET<<warning;
}
void Logger::config(QString config){
    QTextStream out(file);
    out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [config] "<<config;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_CONFIG<<" [config] "<<COLOR_RESET<<config;
}
void Logger::severe(QString severe){
    QTextStream out(file);
    out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [severe] "<<severe;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_SEVERE<<" [severe] "<<COLOR_RESET<<severe;
}

void Logger::info_log(QString information){
      this->info(information);
}

void Logger::config_log(QString config){
    this->config(config);
}
void Logger::warning_log(QString war){
    this->warning(war);
}
void Logger::severe_log(QString sev){
    this->severe(sev);
}
