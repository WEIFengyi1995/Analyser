#ifndef SERCICE_H
#define SERCICE_H
#include<QObject>
class Service:QObject
{
    Q_OBJECT
public:
    virtual void start() = 0;

signals:
    void info(QString action,QString info);
    void config(QString action,QString config);
    void warning(QString action,QString warning);
    void error(QString action,QString error);
};
#endif // SERCICE_H
