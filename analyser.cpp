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
    emit(info("","Analyser initialised"));
    if(this->initAction() !=0){

        emit(error("","can not start the service, check your log file to fix it"));
        qDebug()<<"can not strat the service, check log file";
        this->shell->doShell("rm -r "+constantsTools::PATH_TMP);
        emit start_Error("can not strat the service, check log file");
    }
    {
        emit(info("","Intitialisation done, collecting client information"));
        if(this->clientAction()){
            emit(info("","Start izone"));
            this->ioZone3Action();
            emit(info("","Start nmon "));
            this->nmonAction();
            emit(info("","Start testing Database "));
            this->dbTest();

            emit(info("","Start backup "));
            this->ventapDBBackupAction();
            emit(info("","Service completed, clean up "));
            this->doneAction();
            emit(info("","Finished, you can close the window"));
            emit(finish());
        }
        {
            this->shell->doShell("rm -r "+constantsTools::PATH_TMP);
            emit start_Error("");
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
        emit(error("mkdir -p "+constantsTools::PATH_DB, "exit code anormal, check the dir or your permission"));
    }

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

bool Analyser::clientAction(){

    emit info("client action","check client info ...");
    qDebug()<<"Start client Action";
    DBConnector* db=DBConnector::getDBConnector();
    if(!db->start()){
        emit error("open db","数据库连接失败");
        return false;
    }
    try {
        QSqlQueryModel* result=db->executeQuery(DBConnector::CR_SQL);
        if(result->rowCount()<1){
            emit error("execute query","找不到pvalue");
            return false;
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
            return false;
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
        emit(warning("iozone", "exit code anormal"));
    }

}
void Analyser::nmonAction(){
    qDebug()<<"Start nmon Action";
    int code = shell->doShell("nmon -F "+constantsTools::FILE_NMON+" -t -s "+QString::number(2)+" -c "+
                              QString::number(5));
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

void Analyser::dbTest(){
    verifyDB();


}

void Analyser::verifyDB(){
    int count=0;
    emit info("Verifying main Database "," Begin");
    if(!DBConnector::containsDb(constantsTools::FILE_DB_VENTAP)){
        emit error("Verifying Database","database not found !");
    }else{
        do{
            int i=shell->doShell("gfix -user "+ DBConnector::ISC_USER+" -password "+
                                 DBConnector::ISC_PASSWORD+" -v -full "+ constantsTools::FILE_DB_VENTAP,
                                 constantsTools::FILE_GFIX);
            if(count==3&&i==0){
                emit error("fix db failed after trying 3 times  : ",language::severe.value("A330"));
                break;
            }
            if(i==0){
                emit info("check database ventap",": no problem.");
                if(count>0){
                    emit info("fix databse ",language::severe.value("A411"));
                }
                break;
            }
            else if (i==1){
                count++;
                emit error("check database ",language::severe.value("A330"));
                emit info("fix databse ","trying to fix db for the "+QString(count) +" time" );
                fixDB(0);
            }
            else{
                count++;
                if(count==3){
                    emit error("already fixed db 3 times ",language::severe.value("A132"));
                }
                break;
            }
        }while(count<=3);
    }

    emit info("Verifying Audit Database"," Begin");
    if(!DBConnector::containsDb(constantsTools::FILE_DB_AUDIT)){
        emit error("Verifying Database","database not found !");
    }else{
        do{
            int i=shell->doShell("gfix -user "+ DBConnector::ISC_USER+" -password "+
                                 DBConnector::ISC_PASSWORD+" -v -full "+ constantsTools::FILE_DB_AUDIT,
                                 constantsTools::FILE_GFIX);
            if(count==3&&i==0){
                emit error("fix db failed after trying 3 times  : ",language::severe.value("A330"));
                break;
            }
            if(i==0){
                emit info("check database ventap",": no problem.");
                if(count>0){
                    emit info("fix databse ",language::severe.value("A411"));
                }
                break;
            }
            else if (i==1){
                count++;
                emit error("check database ",language::severe.value("A330"));
                emit info("fix databse ","trying to fix db for the "+QString(count) +" time" );
                fixDB(0);
            }
            else{
                count++;
                if(count==3){
                    emit error("already fixed db 3 times ",language::severe.value("A132"));
                }
                break;
            }
        }while(count<=3);
    }


}



void Analyser::fixDB(int type){
    emit info("fix db ",language::info.value("A412"));
    QString FILE_DB=constantsTools::FILE_DB_VENTAP;
    if(type==1){
        FILE_DB=constantsTools::FILE_DB_AUDIT;
    }
    int i= shell->doShell("gfix -user "+ DBConnector::ISC_USER+" -password "+
                          DBConnector::ISC_PASSWORD+" -mend -full -ignore "+ FILE_DB,
                          constantsTools::FILE_GFIX);
    if(i==1){
        emit info("fix db ",language::info.value("A113"));
    }else if (i==0){
        emit info("fix db ",language::info.value("A213"));
    }else {
        emit error("fix db",language::severe.value("A332"));
    }


}
void Analyser::doneAction(){
    int sum = 0;
    sum += shell->doShell("rm "+constantsTools::FILE_REP+".lck");
    sum += shell->doShell("tar -zcvf "+constantsTools::PATH_VENTAP_DOC+/*DBConnector::getInfoCr()+"_"+
                                                                      QDate::currentDate().toString()+".tar.gz "+*/+"repport.tar.gz "+constantsTools::PATH_TMP);
    sum += shell->doShell("rm -r "+constantsTools::PATH_TMP);
}
