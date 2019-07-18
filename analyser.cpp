#include "analyser.h"
#include "constantstools.h"
#include <QtDebug>
#include <QException>


Analyser * Analyser::instance = nullptr;

void Analyser::start(){
    this->initAction();
    this->clientAction();
    this->ioZone3Action();
    this->nmonAction();
}

Analyser::Analyser()
{
    this->shell = new ShellHandler();
}
Analyser::~Analyser(){
    delete this->shell;
    delete instance;
}

Analyser * Analyser::getAnalyser(){
    if(instance == nullptr){
        instance = new Analyser();
    }
    return instance;

}

//install
void Analyser::initAction(){
    shell->doShell("mkdir -p "+constantsTools::PATH_DB,"");
    shell->doShell("mkdir -p "+constantsTools::PATH_REPORT,"");
    shell->doShell("apt update","");
    shell->doShell("apt install -y -f iozone3","");
    shell->doShell("apt install -y -f nmon","");
}

void Analyser::clientAction(){
    qDebug()<<"Start client Action";
}

void Analyser::ioZone3Action(){
    qDebug()<<"Start ioZone3 Action";
    qDebug()<<shell->doShell("iozone -R -l 5 -u 5 -r 4k -s 100m -F ./p1 ./p2 ./p3 ./p4 ./p4","/home/arcsolu/io.log");

}
void Analyser::nmonAction(){
    qDebug()<<"Start nmon Action";
   // qDebug()<<doShell("iozone -R -l 5 -u 5 -r 4k -s 100m -F ./p1 ./p2 ./p3 ./p4 ./p4","/home/arcsolu/io.log");

}

void Analyser::doneAction(){
    qDebug()<<"Start done Action";
}
