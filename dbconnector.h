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
    //client reference
    static QString info_cr;
    //number
    static QString info_deno;
    //Singeton instance
    static DBConnector* dbConnector;

    const QString ISC_USER="SYSDBA";
    const QString ISC_PASSWORD="masterkey";
    const QString URL="127.0.0.1";
    const int PORT=3050;
    const QString LCC_CTYPE="UNICODE_FSS";
    const QString dbType="QIBASE";
    //  const QString PROTOCOL="jdbc:firebird://";
   // QString dbinfo=PROTOCOL+":"+QString(PORT)+"/"+constantsTools::FILE_DB_VENTAP+"?lc_ctype="+"&user_name="+ISC_USER+"&password="+ISC_PASSWORD;
    QSqlDatabase db;

public:
    static DBConnector* getDBConnector();
    bool start();
    void close();
    static QString getInfoCr();
    static QString getInfoDeno();
    static void setInfoCr(QString cr);
    static void setInfoDeno(QString deno);
    QSqlQueryModel* executeQuery(QString query);
    const QString CR_SQL="select pvalue from t_param where pkey='SYS_CLIENT_REF'; ";
    const QString DENO_SQL="select company from t_title order by create_date asc; ";
};



#endif // DBCONNECTOR_H
