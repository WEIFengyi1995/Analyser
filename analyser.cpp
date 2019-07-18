#include "analyser.h"
#include "constantstools.h"
//#include "dbconnector.h"
#include <QtDebug>
#include <QThread>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlRecord>

Analyser * Analyser::instance = nullptr;

void Analyser::startError(){

}

void Analyser::start(){
    emit(info("","Analyser initialised"));
    if(this->initAction() !=0){
        emit(error("","can not start the service, check your log file to fix it"));
        qDebug()<<"can not strat the service, check log file";
        this->shell->doShell("rm -r "+constantsTools::PATH_TMP);
        emit startError();
    }else{
        emit(info("","Intitialisation done, collecting client information"));
        this->clientAction();
        emit(info("","Start izone"));
        this->ioZone3Action();
        emit(info("","Start nmon "));
        this->nmonAction();
        emit(info("","Start backup "));
        this->ventapDBBackupAction();
        emit(info("","Service completed, clean up "));
    }

    //this->doneAction();
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

int Analyser::initAction(){
    int sum = 0;
    int code;
    code = shell->doShell("mkdir -p "+constantsTools::PATH_DB,"");
    sum += code;
    if(code != 0){
        emit(error("mkdir -p "+constantsTools::PATH_DB, "exit code anormal, check the dir or your permission"));
    }
    sum += code;

    code = shell->doShell("mkdir -p "+constantsTools::PATH_REPORT,"");
    if(code != 0){
        emit(error("mkdir -p "+constantsTools::PATH_REPORT, "exit code anormal, check the dir"));
    }
    sum += code;

    code = shell->doShell("apt update","");
    if(code != 0){
        emit(error("apt update ", "exit code anormal, check your permission"));
    }
    sum += code;

    code = shell->doShell("apt install -y -f iozone3","");
    if(code != 0){
        emit(error("apt install -y -f iozone3","can not install iozone3"));
    }
    sum += code;

    code = shell->doShell("apt install -y -f nmon","");
    if(code != 0){
        emit(error("apt install -y -f nmon","can not install nmon"));
    }
    sum += code;

    return sum;
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
        exit(1);
    }{
        db->close();
    }

}

void Analyser::ioZone3Action(){
    qDebug()<<"Start ioZone3 Action";
    int code = shell->doShell("iozone -R -l 5 -u 5 -r 4k -s 100m -F "+constantsTools::PATH_TMP+"f1 "+constantsTools::PATH_TMP+"f2 "+
                             constantsTools::PATH_TMP+"f3 "+constantsTools::PATH_TMP+"f4 "+constantsTools::PATH_TMP+"f5 ",
                             constantsTools::FILE_IOZONE);
    if(code != 0){
        emit(warning("iozone", "exit code anormal"));
    }

}
void Analyser::nmonAction(){
    qDebug()<<"Start nmon Action";
    int code = shell->doShell("nmon -F "+constantsTools::FILE_NMON+" -t -s "+QString::number(2)+" -c "+
                             QString::number(5));
    if(code != 0){
        emit(warning("nmon","exit code anmorl"));
    }
    QThread::msleep((2*5+5)*1000);

}

void Analyser::ventapDBBackupAction(){
    qDebug()<<"Start backup action";
}
void Analyser::doneAction(){
    int sum = 0;
    sum += shell->doShell("rm "+constantsTools::FILE_REP+".lck");
    sum += shell->doShell("tar -zcvf "+constantsTools::PATH_VENTAP_DOC+/*DBConnector::getInfoCr()+*/"_"+
                          QDate::currentDate().toString()+".tar.gz "+constantsTools::PATH_TMP);
    sum += shell->doShell("rm -r "+constantsTools::PATH_TMP);
}
