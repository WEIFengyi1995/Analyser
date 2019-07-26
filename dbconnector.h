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
    const static QString CR_SQL;
    const static QString DENO_SQL;

    static void setInfoCr(QString cr);
    static void setInfoDeno(QString deno);
    //  const QString PROTOCOL="jdbc:firebird://";
    // QString dbinfo=PROTOCOL+":"+QString(PORT)+"/"+constantsTools::FILE_DB_VENTAP+"?lc_ctype="+"&user_name="+ISC_USER+"&password="+ISC_PASSWORD;
    static QSqlDatabase db;
    static QSqlDatabase dbAudit;

public:
    /*!
     * \brief getDBConnector
     * get the singleton instance
     * \return
     */
    static DBConnector* getDBConnector();
    /*!
     * \brief start
     * config connextion
     * \return
     */
    static bool start();
    /*!
     * \brief containsDb
     * \param name
     * \return true if conatins database named name
     */
    static bool containsDb(QString name);
    static void close();
    /*!
     * \brief getInfoCr
     * get information client reference
     * \return
     */
    static QString getInfoCr();
    /*!
     * \brief getInfoDeno
     * \return
     */
    static QString getInfoDeno();
    const static QString ISC_USER;
    const static QString ISC_PASSWORD;
    const static QString URL;
    const static int PORT;
    const static QString LCC_CTYPE;
    const static QString dbType;
    /*!
     * \brief search Client Reference using query
     * \return
     */
    static bool searchCR();
    /*!
     * \brief search DENO search deNO using query
     * \return
     */
    static bool searchDENO();
};



#endif // DBCONNECTOR_H
