#include "singleinstance.h"
#include <QtNetwork/QLocalSocket>
#include <QtDebug>

SingleInstance::SingleInstance(MainWindow &w, QString name){
    this->w = &w;
    this->name = name;
    QObject::connect(&server,SIGNAL(newConnection()),this,SLOT(newConnection()),Qt::DirectConnection);
}

SingleInstance::~SingleInstance(){
    server.removeServer(name);
    this->server.close();
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

bool SingleInstance::listen(){
    this->server.removeServer(name);
    if(this->server.listen(name)){
        return true;
    }
    else{
        return false;
    }
}

void SingleInstance::newConnection(){
    qDebug()<<"show window";
    this->client = this->server.nextPendingConnection();
    this->w->show();
}

void SingleInstance::show(){
    qDebug()<<"show window";
    this->w->show();
}
