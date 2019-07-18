#include "analyser.h"
#include "constantstools.h"
#include <QtDebug>
#include <QThread>
#include <QSqlQueryModel>
#include <QSqlRecord>

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
    emit info("ini","initAction...");

    shell->doShell("mkdir -p "+constantsTools::PATH_DB,"");
    shell->doShell("mkdir -p "+constantsTools::PATH_REPORT,"");
    shell->doShell("apt update","");
    shell->doShell("apt install -y -f iozone3","");
    shell->doShell("apt install -y -f nmon","");
}

void Analyser::clientAction(){

    emit info("client action","check client info ...");
    qDebug()<<"Start client Action";
    DBConnector* db=DBConnector::getDBConnector();
    if(!db->start()){
        emit error("open db","数据库连接失败");
    }
    try {
        QSqlQueryModel* result=db->executeQuery(db->CR_SQL);
        if(result->rowCount()<1){
            emit error("execute query","找不到pvalue");
        }
        QString cr= result->record(0).value("pvalue").toString();
        if(!cr.isEmpty()){
            emit config("find pvalue!","configuration ok");
        }else{
            emit warning("pvalue error","empty!");
        }
        DBConnector::setInfoCr(cr);

        QSqlQueryModel* result2=db->executeQuery(db->DENO_SQL);
        if(result2->rowCount()<1){
            emit error("execute query","company  deno no found ");
        }
        QString deno= result->record(0).value("company").toString();
        if(!deno.isEmpty()){
            emit config("find deno ","configuration ok");
        }else{
            emit warning("deno error ","empty!");
        }
        DBConnector::setInfoCr(deno);
    } catch (...) {
        emit error("error","A230");
        shell->doShell("rm -r "+constantsTools::PATH_TMP,"");
    }{
        db->close();
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
