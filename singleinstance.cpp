#include "singleinstance.h"
#include <QtNetwork/QLocalSocket>

SingleInstance::SingleInstance(MainWindow &w, QString name){
    this->w = &w;
    this->name = name;
    this->client = nullptr;
    QObject::connect(&server,SIGNAL(newConnection()),this,SLOT(newConnection()),Qt::DirectConnection);
}

SingleInstance::~SingleInstance(){
    server.removeServer(name);
    this->server.close();
    if(client != nullptr){
        delete client;
    }
}

bool SingleInstance::checkInstance(QString name){
    QLocalSocket client;
    client.connectToServer(name,QLocalSocket::ReadWrite);
    if(client.waitForConnected(1000)){
        return true;
    }
    else{
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
    this->client = this->server.nextPendingConnection();
    this->w->show();
}
