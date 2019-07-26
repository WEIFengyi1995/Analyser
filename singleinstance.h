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
    /*!
     * \brief checkInstance
     * check if there is a server listening to the name
     * if yes, application is already runnning
     * \param name
     * \return
     */
    static bool checkInstance(QString name);
    /*!
     * \brief listen
     *
     * let socket server listen to name
     *
     * \return
     */
    bool listen();

private:
    MainWindow *w;
    QLocalServer server;
    QLocalSocket * client;
    QString name;

private slots:
    void newConnection();
};

#endif // SINGLEINSTANCE_H
