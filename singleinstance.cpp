#include "singleinstance.h"
#include <QtNetwork/QLocalSocket>
#include <QtDebug>

SingleInstance::SingleInstance(MainWindow &w, QString name){
    this->w = &w;
    this->name = name;
    QObject::connect(&server,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

SingleInstance::~SingleInstance(){
    //delete w;
    server.removeServer(name);
}
bool SingleInstance::checkInstance(QString name){
    QLocalSocket client;
    client.connectToServer(name,QLocalSocket::ReadWrite);
    if(client.waitForConnected(1000)){
        qDebug()<<"connected";
        return true;
    }
    else{
        qDebug()<<client.errorString();
        return false;
    }
}

void SingleInstance::listen(){
    this->server.removeServer(name);
    this->server.listen(name);
}

void SingleInstance::newConnection(){
    this->client = this->server.nextPendingConnection();
    connect(client,SIGNAL(readyRead()),this,SLOT(show()));
}

void SingleInstance::show(){
    this->w->show();
}
