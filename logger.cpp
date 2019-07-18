#include "logger.h"
#include<QTextStream>
#include<QFile>
#include<QDateTime>
#include<QDebug>
#include<QDir>

Logger::Logger(QString file1)
{
    FileName=file1;

}

void Logger::info(QString info){
    QDir dir;
    QFile file(FileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"error"<<FileName;
        return;
    }
    QTextStream out(&file);
    out <<QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [info] "<<info;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_INFO<<" [info] "<<COLOR_RESET<<info;
    file.close();
}
void Logger::warning(QString warning){
    QFile file(FileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [warning] "<<warning;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_WARNNING<<" [warning] "<<COLOR_RESET<<warning;
    file.close();
}
void Logger::config(QString config){
    QFile file(FileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [config] "<<config;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_CONFIG<<" [config] "<<COLOR_RESET<<config;
    file.close();
}
void Logger::severe(QString severe){
    QFile file(FileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << QDateTime().currentDateTime().toString(DATE_FORMAT)<<" [severe] "<<severe;
    qDebug()<<QDateTime().currentDateTime().toString(DATE_FORMAT)<<COLOR_SEVERE<<" [severe] "<<COLOR_RESET<<severe;
    file.close();
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
