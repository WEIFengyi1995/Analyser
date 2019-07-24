#include "analyser.h"
#include "constantstools.h"
#include "language.h"
#include <QtDebug>
#include <QThread>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include "tool.h"
#include "myapplication.h"


Analyser * Analyser::instance = nullptr;


Analyser::~Analyser(){
    delete this->shell;
    delete instance;
}

Analyser::Analyser(Logger &log)
{
    this->shell = new ShellHandler();

    this->log = &log;
}

//ini->clientAction->gfix->gbackup->iozone->nmon
void Analyser::start(){

    if(this->initAction() !=0){
        emit(error("","can not start the service, check your log file to fix it"));
        this->shell->doShell("rm -r "+constantsTools::PATH_TMP);
        emit finish("can not start the service, check "+constantsTools::FILE_REP);
    }else{

        emit(info("Iniatialisation","successfull, collecting client information"));
        if(this->clientAction()){
            emit(info("gfix","Start testing Database "));
            this->dbTest();
            emit info("gifix","test done ");
            emit(info("","Start backup "));
            emit(info("DBBackup","initialisation..."));
            this->ventapDBBackupAction();
            emit(info("DBBAckup","done"));
            emit(info("ioZone","initialisation..."));
            //this->ioZone3Action();
            emit(info("ioZone","done"));
            emit(info("nmon","initialisation..."));
            //this->nmonAction();
            emit(info("nmon","done"));
            emit(info("Compress","initialisation..."));
            this->doneAction();
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
    code = shell->doShell("mkdir -p "+constantsTools::PATH_REPORT);
    if(code != 0){
        emit finish("Can not create "+constantsTools::PATH_REPORT+", check your permission");
        return -1;
     }
    this->log->setFile(constantsTools::FILE_REP);
    emit(info("Initialisation","analyser initialised"));
    code = shell->doShell("mkdir -p "+constantsTools::PATH_DB,"");
    sum += code;
    if(code != 0){
        emit(error("mkdir -p "+constantsTools::PATH_DB, "exit code anormal, check your permission"));
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
    DBConnector* db=DBConnector::getDBConnector();

    if(!db->start()){
        emit error("open db","数据库连接失败");
        //emit finish(language::severe.value("A230"));
        //return false;
    }
    try {
        bool cr=  DBConnector::searchCR();
        bool deno = DBConnector::searchDENO();

        if(!cr){
            emit error("execute query","找不到pvalue");
            //emit finish(language::severe.value("A230"));
            //return false;
        }
        else{
            emit config("find pvalue!","configuration ok");
            emit config("ok!",language::config.value("A100"));
        }

        if(!deno){
            emit error("execute query","company  deno no found ");
            //emit finish(language::severe.value("A230"));
        }else{
            emit config("find deno ","configuration ok");
            emit config("ok!",language::config.value("A101"));
        }
    } catch (...) {
        emit error("error","A230");
        emit finish(language::severe.value("A230"));
        shell->doShell("rm -r "+constantsTools::PATH_TMP,"");
        return false;

    }{
        db->close();
        emit info("DB",language::info.value("A210"));
    }
    return true;

}

void Analyser::ioZone3Action(){
    emit info("iozone",language::info.value("A215"));

    int code = shell->doShell("iozone -R -l 5 -u 5 -r 4k -s 100m -F "+constantsTools::PATH_TMP+"f1 "+constantsTools::PATH_TMP+"f2 "+
                              constantsTools::PATH_TMP+"f3 "+constantsTools::PATH_TMP+"f4 "+constantsTools::PATH_TMP+"f5 ",
                              constantsTools::FILE_IOZONE);
    if(code != 0){
        emit(warning("ioZone", "exit code anormal"));
    }

}
void Analyser::nmonAction(){
    emit info("collecting sample","( "+QString::number(1)+"/"+QString::number(constantsTools::SAMPLE)+" )");
    int code = shell->doShell("nmon -F "+constantsTools::FILE_NMON);
    if(code != 0){
        emit(warning("nmon","exit code anormal"));
    }

    QTime time=QTime().currentTime().addMSecs(constantsTools::INTERVAL*1000+1000);
    while(time>QTime().currentTime()){}

    for(int i=1;i<constantsTools::SAMPLE;i++){
        emit info("collecting sample","( "+QString::number(i+1)+"/"+QString::number(constantsTools::SAMPLE)+" )");
        QString error;
        QString tmpFile=constantsTools::PATH_REPORT+"tmp";
        int code = shell->doShell("nmon -F "+tmpFile);
        if(code != 0){
            emit(warning("nmon","exit code anormal"));
        }
        QTime time=QTime().currentTime().addMSecs(constantsTools::INTERVAL*1000+1000);
        while(time>QTime().currentTime()){}
        if(!cutFile(tmpFile , constantsTools::FILE_NMON,i,1,error )){
            emit(warning("move result ",error));
        }
    }
}

void Analyser::ventapDBBackupAction(){
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
                emit info("fix databse ","trying to fix db for the "+QString::number(count) +" time" );
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
                emit info("fix databse ","trying to fix db for the "+QString::number(count) +" time" );
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
    sum += shell->doShell("tar -zcvf "+constantsTools::PATH_VENTAP_DOC+DBConnector::getInfoCr()+"_"+ QDate::currentDate().toString(constantsTools::DATE_FORMAT)+".tar.gz "+constantsTools::PATH_TMP,"");
    shell->doShell("chown ventap:ventap "+constantsTools::PATH_VENTAP_DOC+DBConnector::getInfoCr()+"_"+ QDate::currentDate().toString(constantsTools::DATE_FORMAT)+".tar.gz ");
    shell->doShell("rm -r "+constantsTools::PATH_TMP);
    shell->doShell("rm -f "+constantsTools::FILE_REP);
}
