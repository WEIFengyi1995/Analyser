#include "analyser.h"
#include "constantstools.h"
#include "language.h"
#include <QtDebug>
#include <QThread>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlRecord>


Analyser * Analyser::instance = nullptr;


Analyser::~Analyser(){
    delete this->shell;
    delete instance;
}

Analyser::Analyser(Logger &log)
{
    this->shell = new ShellHandler();
    shell->doShell("mkdir -p "+constantsTools::PATH_TMP,"");
    this->log = &log;
    this->log->setFile(constantsTools::FILE_REP);
}


void Analyser::start(){
    emit(info("Initialisation","analyser initialised"));
    if(this->initAction() !=0){
        emit(error("Initialisation","can not start the service"));
        this->shell->doShell("rm -r "+constantsTools::PATH_TMP);

        emit finish("can not start the service, check "+constantsTools::FILE_REP);
    }else{
        emit(info("Iniatialisation","successfull, collecting client information"));
        if(this->clientAction()){
            emit(info("ioZone","initialisation..."));
            this->ioZone3Action();
            emit(info("ioZone","done"));
            emit(info("nmon","initialisation..."));
            this->nmonAction();
            emit(info("nmon","done"));
            emit(info("DBBackup","initialisation..."));
            this->ventapDBBackupAction();
            emit(info("DBBAckup","done"));
            emit(info("Compress","initialisation..."));
            this->doneAction();
            emit(info("Compress","done"));
            emit(info("Analyser","finished, you can close the window"));
            emit(finish("Sucessfull"));
        }
        else{
            emit(error("Client"," failed"));
            this->shell->doShell("rm -r "+constantsTools::PATH_TMP);
            emit finish("Client not found, check your log file");
        }
    }
}


Analyser * Analyser::getAnalyser(Logger &log){
    if(instance == nullptr){
        instance = new Analyser(log);
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
        emit(error("mkdir -p "+constantsTools::PATH_DB, "exit code anormal, check your permission"));
    }

    code = shell->doShell("mkdir -p "+constantsTools::PATH_REPORT);
    if(code != 0){
        emit(error("mkdir -p "+constantsTools::PATH_REPORT, "exit code anormal, check your permission"));
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

bool Analyser::clientAction(){
    emit info("client action","check client info ...");
    qDebug()<<"Start client Action";
    DBConnector* db=DBConnector::getDBConnector();
    if(!db->start()){
        emit error("open db","数据库连接失败");
        //return false;
    }
    try {
        QSqlQueryModel* result=db->executeQuery(DBConnector::CR_SQL);
        if(result->rowCount()<1){
            emit error("execute query","找不到pvalue");
            //return false;
        }
        QString cr= result->record(0).value("pvalue").toString();
        if(!cr.isEmpty()){
            emit config("find pvalue!","configuration ok");
        }else{
            emit warning("pvalue error","empty!");
        }
        DBConnector::setInfoCr(cr);

        QSqlQueryModel* result2=db->executeQuery(DBConnector::DENO_SQL);
        if(result2->rowCount()<1){
            emit error("execute query","company  deno no found ");
            //return false;
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
    return true;

}

void Analyser::ioZone3Action(){
    qDebug()<<"Start ioZone3 Action";
    int code = shell->doShell("iozone -R -l 5 -u 5 -r 4k -s 100m -F "+constantsTools::PATH_TMP+"f1 "+constantsTools::PATH_TMP+"f2 "+
                             constantsTools::PATH_TMP+"f3 "+constantsTools::PATH_TMP+"f4 "+constantsTools::PATH_TMP+"f5 ",
                             constantsTools::FILE_IOZONE);
    if(code != 0){
        emit(warning("ioZone", "exit code anormal"));
    }

}
void Analyser::nmonAction(){
    qDebug()<<"Start nmon Action";
    int code = shell->doShell("nmon -F "+constantsTools::FILE_NMON+" -t -s "+QString::number(constantsTools::SAMPLE)+" -c "+
                             QString::number(constantsTools::INTERVAL));
    if(code != 0){
        emit(warning("nmon","exit code anormal"));
    }
    QThread::msleep((2*5+5)*1000);

}

void Analyser::ventapDBBackupAction(){
    qDebug()<<"Start backup action";
    int i=shell->doShell("gbak -user "+DBConnector::ISC_USER+" -password "+DBConnector::ISC_PASSWORD+" -backup -v -ignore "
                         +constantsTools::FILE_DB_VENTAP+" "+constantsTools::FILE_DBK_VENTAP,constantsTools::FILE_GBAK);
    if(i==1){
       emit info("gbak db_ventap",language::info.value("A211"));
    }else if(i==0){
        emit warning("gbak db_ventap"," db backup warning? ");
    }else{
        emit error("gbak db_ventap"," db backup error");
    }

    int j=shell->doShell("gbak -user "+DBConnector::ISC_USER+" -password "+DBConnector::ISC_PASSWORD+" -backup -v -ignore "
                         +constantsTools::FILE_DB_AUDIT+" "+constantsTools::FILE_DBK_AUDIT, constantsTools::FILE_GBAK);
    if(j==1){
       emit info("gbak db_AUDIT"," sucess");
    }else if(j==0){
        emit warning("gbak db_AUDIT"," db backup warning? ");
    }else{
        emit error("gbak db_AUDIT"," db backup error");
    }


}

void Analyser::doneAction(){
    int sum = 0;
    sum += shell->doShell("rm "+constantsTools::FILE_REP+".lck");
    sum += shell->doShell("tar -zcvf "+constantsTools::PATH_VENTAP_DOC+/*DBConnector::getInfoCr()+"_"+
                          QDate::currentDate().toString()+".tar.gz "+*/+"repport.tar.gz "+constantsTools::PATH_TMP+" "+constantsTools::FILE_REP);
    shell->doShell("rm -r "+constantsTools::PATH_TMP);
    shell->doShell("rm -f "+constantsTools::FILE_REP);
}
