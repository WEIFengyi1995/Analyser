#include "analyser.h"
#include "analyserutils.h"
#include <QtDebug>

Analyser * Analyser::instance = nullptr;

void Analyser::start(){
    this->initAction();
    this->clientAction();
    this->ioZone3Action();
    this->nmonAction();
}

Analyser::Analyser()
{
}

Analyser * Analyser::getAnalyser(){
    if(instance == nullptr){
        instance = new Analyser();
    }
    return instance;

}

void Analyser::initAction(){
    qDebug()<<"Start init Action";

}

void Analyser::clientAction(){
    qDebug()<<"Start client Action";
}

void Analyser::ioZone3Action(){
    qDebug()<<"Start ioZone3 Action";
    qDebug()<<doShell("iozone -R -l 5 -u 5 -r 4k -s 100m -F ./p1 ./p2 ./p3 ./p4 ./p4","/home/arcsolu/io.log");

}
void Analyser::nmonAction(){
    qDebug()<<"Start nmon Action";
   // qDebug()<<doShell("iozone -R -l 5 -u 5 -r 4k -s 100m -F ./p1 ./p2 ./p3 ./p4 ./p4","/home/arcsolu/io.log");

}

void Analyser::doneAction(){
    qDebug()<<"Start done Action";
}
