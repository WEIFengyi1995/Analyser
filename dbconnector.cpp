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
    qDebug()<<URL<<constantsTools::FILE_DB_VENTAP;
    qDebug()<<ISC_USER<<ISC_PASSWORD;
    bool ok=db.open();
    return ok;
}

bool DBConnector::containsDb(QString name){
    return db.contains(name);
}
void DBConnector::close(){
    db.close();
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

QSqlQueryModel* DBConnector::executeQuery(QString query){
    QSqlQuery sql(QSqlDatabase::database(constantsTools::FILE_DB_VENTAP));
    if(!sql.exec(query)){
        qDebug()<<"exec query failed!";
    }
    QSqlQueryModel* result=new QSqlQueryModel();
    result->setQuery(sql);
    return result;
}




