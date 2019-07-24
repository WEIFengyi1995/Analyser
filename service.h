#ifndef SERCICE_H
#define SERCICE_H
#include<QObject>
class Service:public QObject
{
    Q_OBJECT

public slots:
    virtual void start() = 0;

signals:
    void info(QString action,QString info);
    void config(QString action,QString config);
    void warning(QString action,QString warning);
    void error(QString action,QString error);
    void finish(QString str);

};
#endif // SERCICE_H
