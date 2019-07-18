#include "dbconnector.h"
#include<QSqlQuery>
#include <QDebug>
DBConnector::DBConnector()
{
}
DBConnector* DBConnector::dbConnector=nullptr;
QString DBConnector::info_cr="";
QString DBConnector::info_deno="";
DBConnector* DBConnector::getDBConnector(){
    if(dbConnector==nullptr){
        dbConnector=new DBConnector();
    }
    return dbConnector;
}

bool DBConnector::start(){
    db=QSqlDatabase::addDatabase(dbType,"db");
    db.setUserName(ISC_USER);
    db.setPassword(ISC_PASSWORD);
    db.setHostName(URL);
    db.setDatabaseName(constantsTools::FILE_DB_VENTAP);
    qDebug()<<URL<<constantsTools::FILE_DB_VENTAP;
    qDebug()<<ISC_USER<<ISC_PASSWORD;
    bool ok=db.open();
    return ok;
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
    QSqlQuery sql(QSqlDatabase::database("db"));
    if(!sql.exec(query)){
        qDebug()<<"exec query failed!";
    }
    QSqlQueryModel* result=new QSqlQueryModel();
    result->setQuery(sql);
    return result;
}




