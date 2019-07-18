#ifndef SERCICE_H
#define SERCICE_H
#include<QObject>
class Service:public QObject
{
    Q_OBJECT
public slots:
    virtual void start() = 0;


signals:
    void info(QString info);
    void config(QString config);
    void warning(QString warning);
    void error(QString error);
};
#endif // SERCICE_H
