#include "analyser.h"
#include "constantstools.h"
#include <QtDebug>
#include <QThread>
#include "dbconnector.h"

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
    emit info("initAction...");
    shell->doShell("mkdir -p "+constantsTools::PATH_DB,"");
    shell->doShell("mkdir -p "+constantsTools::PATH_REPORT,"");
    shell->doShell("apt update","");
    shell->doShell("apt install -y -f iozone3","");
    shell->doShell("apt install -y -f nmon","");
}

void Analyser::clientAction(){
    emit info("check client info ...");
    qDebug()<<"Start client Action";
    DBConnector* db=DBConnector::getDBConnector();
    if(!db->start()){
        emit error("数据库连接失败");
    }
    try {
        QSqlQueryModel* result=db->executeQuery(db->CR_SQL);



    } catch (...) {

    }{
    }


}

void Analyser::ioZone3Action(){
    qDebug()<<"Start ioZone3 Action";
    qDebug()<<shell->doShell("iozone -R -l 5 -u 5 -r 4k -s 100m -F "+constantsTools::PATH_TMP+"f1 "+constantsTools::PATH_TMP+"f2 "+
                             constantsTools::PATH_TMP+"f3 "+constantsTools::PATH_TMP+"f4 "+constantsTools::PATH_TMP+"f5 ",
                             constantsTools::FILE_IOZONE);

}
void Analyser::nmonAction(){
    qDebug()<<"Start nmon Action";
    qDebug()<<shell->doShell("nmon -F "+constantsTools::FILE_NMON+" -t -s "+QString::number(2)+" -c "+
                             QString::number(5));
    QThread::msleep((2*5+5)*1000);

}

void Analyser::ventapDBBackupAction(){
qDebug()<<"Start backup action";
}
void Analyser::doneAction(){
    qDebug()<<"Start done Action";
}
