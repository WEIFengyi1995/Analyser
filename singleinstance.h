#ifndef SINGLEINSTANCE_H
#define SINGLEINSTANCE_H
#include "mainwindow.h"
#include <QtNetwork/QLocalServer>


class SingleInstance: public QObject
{
    Q_OBJECT
public:
    SingleInstance(MainWindow  & w, QString name);
    ~SingleInstance();

    static bool checkInstance(QString name);
    void listen();

private:
    MainWindow *w;
    QLocalServer server;
    QLocalSocket * client;
    QString name;

private slots:
    void newConnection();
    void show();

};

#endif // SINGLEINSTANCE_H
