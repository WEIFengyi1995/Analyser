#include "constantstools.h"


const QString constantsTools::PRODUCT="ventap";
const QString constantsTools::SERVER_NAME = "singleService";
const QString constantsTools::PATH_DB=QString(QDir::separator())+"var"+QString(QDir::separator())+"lib"+QString(QDir::separator())+"firebird"
        +QString(QDir::separator())+"2.5"+QString(QDir::separator())+"data"+QString(QDir::separator());
//const QString constantsTools::PATH_VENTAP_HOME=QString(QDir::separator())+"home"+QString(QDir::separator())+PRODUCT+QString(QDir::separator());
const QString constantsTools::PATH_VENTAP_HOME = QDir().homePath()+QDir::separator()+PRODUCT+QDir::separator();
const QString constantsTools:: PATH_VENTAP_DOC=PATH_VENTAP_HOME+"Documents"+QString(QDir::separator());
const QString constantsTools::PATH_TMP=PATH_VENTAP_DOC+".tmp"+QString(QDir::separator());
const QString constantsTools::PATH_DBK=PATH_TMP+"db"+QString(QDir::separator());
const QString constantsTools::PATH_REPORT=PATH_TMP+"system"+QString(QDir::separator());


const QString constantsTools::FILE_DB_VENTAP=PATH_DB+"ventap.fdb";
const QString constantsTools::FILE_DB_AUDIT=PATH_DB+"audit.fdb";
const QString constantsTools::FILE_DBK_VENTAP=PATH_DBK+"ventap.fbk";
const QString constantsTools::FILE_DBK_AUDIT=PATH_DBK+"audit.fbk";
const QString constantsTools::FILE_REP=constantsTools::PATH_VENTAP_DOC+"report.log";
const QString constantsTools::FILE_NMON=PATH_REPORT+"nm.log";
const QString constantsTools::FILE_IOZONE=PATH_REPORT+"io.log";
const QString constantsTools::FILE_GFIX=PATH_REPORT+"gf.log";
const QString constantsTools::FILE_GBAK=PATH_REPORT+"gb.log";
const QString constantsTools::FILE_TERM=PATH_REPORT+"tm.log";
const int constantsTools::WAIT_TIME =(6000)*1000;

const int constantsTools::SAMPLE  = 10;
const int constantsTools::INTERVAL = 2;
const QString constantsTools::DATE_FORMAT="yyyy-MM-dd HH:mm:ss.zzz";

constantsTools::constantsTools()
{
}

