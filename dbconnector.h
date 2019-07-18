#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H
#include<QString>
#include<QObject>
#include<QSqlDatabase>
#include<QSqlQueryModel>
#include<QObject>
#include "constantstools.h"
class DBConnector:public QObject
{
private:
    DBConnector();
    static DBConnector* dbConnector;
    const QString ISC_USER="SYSDBA";
    const QString ISC_PASSWORD="masterkey";
    const QString URL="127.0.0.1";
    const QString PROTOCOL="jdbc:firebird://";
    const int PORT=3050;
    const QString LCC_CTYPE="UNICODE_FSS";
    const QString CR_SQL="select pvalue from t_param where pkey='SYS_CLIENT_REF'; ";
    const QString DEMO_SQL="select company from t_title order by create_date asc; ";
    static QString info_cr;
    static QString info_deno;
    QString dbinfo=PROTOCOL+":"+QString(PORT)+"/"+constantsTools::FILE_DB_VENTAP+"?lc_ctype="+"&user_name="+ISC_USER+"&password="+ISC_PASSWORD;
    QSqlDatabase db;

public:
    static DBConnector* getDBConnector();
    bool start();
    static QString getInfoCr();
    static QString getInfoDeno();
    static void setInfoCr(QString cr);
    static void setInfoDeno(QString deno);
    QSqlQueryModel* executeQuery(QString query);

};
DBConnector* DBConnector::dbConnector=nullptr   ;
QString DBConnector::info_cr="";
QString DBConnector::info_deno="";


#endif // DBCONNECTOR_H
