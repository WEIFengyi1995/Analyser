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
    const static QString ISC_USER;
    const static QString ISC_PASSWORD;
    const static QString URL;
    const static int PORT;
    const static QString LCC_CTYPE;
    const static QString dbType;
    const static QString CR_SQL;
    const static QString DENO_SQL;
};



#endif // DBCONNECTOR_H
