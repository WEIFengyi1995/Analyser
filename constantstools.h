#ifndef CONSTANTSTOOLS_H
#define CONSTANTSTOOLS_H

#include <QDir>
#include <QString>
class constantsTools
{
public:
    constantsTools();
     const QString  PRODUCT="ventap";
    const QString PATH_DB=QString(QDir::separator())+"var"+QString(QDir::separator())+"lib"+QString(QDir::separator())+"firebird"
            +QString(QDir::separator())+"2.5"+QString(QDir::separator())+"data"+QString(QDir::separator());
    const QString PATH_VENTAP_HOME=QString(QDir::separator())+"home"+QString(QDir::separator())+PRODUCT+QString(QDir::separator());
    const QString PATH_VENTAP_DOC=PATH_VENTAP_HOME+"Documents"+QString(QDir::separator());
    const QString PATH_TMP=PATH_VENTAP_DOC+".tmp"+QString(QDir::separator());
    const QString PATH_DBK=PATH_TMP+"db"+QString(QDir::separator());
    const QString PATH_REPORT=PATH_TMP+"system"+QString(QDir::separator());

    const QString FILE_DB_VENTAP=PATH_DB+"ventap.fdb";
    const QString FILE_DB_AUDIT=PATH_DB+"audit.fdb";
    const QString FILE_DBK_VENTAP=PATH_DBK+"ventap.fbk";
    const QString FILE_DBK_AUDIT=PATH_DBK+"audit.fbk";
    const QString FILE_REP=PATH_TMP+"report.log";
    const QString FILE_NMON=PATH_REPORT+"nm.log";
    const QString FILE_IOZONE=PATH_REPORT+"io.log";
    const QString FILE_GFIX=PATH_REPORT+"gf.log";
    const QString FILE_GBAK=PATH_REPORT+"gb.log";
    const QString FILE_TERM=PATH_REPORT+"tm.log";
};





#endif // CONSTANTSTOOLS_H
