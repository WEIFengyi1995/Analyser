#include "dbconnector.h"
#include<QSqlQuery>
#include <QDebug>
#include <QSqlDatabase>
DBConnector::DBConnector()
{
}
DBConnector* DBConnector::dbConnector=nullptr;
QString DBConnector::info_cr="";
QString DBConnector::info_deno="";
QSqlDatabase DBConnector::db;
QSqlDatabase DBConnector::dbAudit;
const QString DBConnector::ISC_USER="SYSDBA";
const QString DBConnector::ISC_PASSWORD="masterkey";
const QString DBConnector::URL="127.0.0.1";
const int DBConnector::PORT=3050;
const QString DBConnector::LCC_CTYPE="UNICODE_FSS";
const QString DBConnector::dbType="QIBASE";
const QString DBConnector::CR_SQL="select pvalue from t_param where pkey='SYS_CLIENT_REF'; ";
const QString DBConnector::DENO_SQL="select company from t_title order by create_date asc; ";
DBConnector* DBConnector::getDBConnector(){
    if(dbConnector==nullptr){
        dbConnector=new DBConnector();
    }
    return dbConnector;
}

bool DBConnector::start(){
    db=QSqlDatabase::addDatabase(dbType,constantsTools::FILE_DB_VENTAP);
    db.setUserName(ISC_USER);
    db.setPassword(ISC_PASSWORD);
    db.setHostName(URL);
    db.setDatabaseName(constantsTools::FILE_DB_VENTAP);
    bool ok=db.open();
    dbAudit=QSqlDatabase::addDatabase(dbType,constantsTools::FILE_DB_AUDIT);
    dbAudit.setUserName(ISC_USER);
    dbAudit.setPassword(ISC_PASSWORD);
    dbAudit.setHostName(URL);
    dbAudit.setDatabaseName(constantsTools::FILE_DB_AUDIT);
    bool okAudit=dbAudit.open();
    return ok&&okAudit;
}

bool DBConnector::containsDb(QString name){
    return QSqlDatabase::contains(name);
}
void DBConnector::close(){
    db.close();
    dbAudit.close();
}
QString DBConnector::getInfoCr(){
    return info_cr;
}
QString DBConnector::getInfoDeno(){
    return info_deno;
}

void DBConnector::setInfoCr(QString cr){
    info_cr=cr;
}
void DBConnector::setInfoDeno(QString deno){
    info_deno=deno;
}

bool DBConnector::searchCR(){
    QSqlQuery sql(QSqlDatabase::database(constantsTools::FILE_DB_VENTAP));
    if(!sql.exec(CR_SQL)){
        qDebug()<<"exec query failed!";
    }
    if(sql.next()){
        setInfoCr(sql.value("pvalue").toString());
        return true;
    }
    return false;
}

bool DBConnector::searchDENO(){
    QSqlQuery sql(QSqlDatabase::database(constantsTools::FILE_DB_VENTAP));
    if(!sql.exec(DENO_SQL)){
        qDebug()<<"exec query failed!";
    }
    if(sql.next()){
        setInfoCr(sql.value("company").toString());
        return true;
    }
    return false;
}



