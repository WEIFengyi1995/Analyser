#ifndef ANALYSER_H
#define ANALYSER_H
#include "service.h"
#include "shellhandler.h"
#include "dbconnector.h"
#include "logger.h"
#include <QSettings>
#include <QThread>

class Analyser:public Service
{
    Q_OBJECT
public:
    static Analyser *getAnalyser(Logger &log);
    ~Analyser();
public slots:
    /*!
     * \brief start
     * start sevices
     */
    void start();
private:
    static Analyser *instance;
    Analyser(Logger &log);
    ShellHandler * shell = nullptr;
    Logger * log;
    /*!
     * \brief INTERVAL
     * nmon interval
     */
    int INTERVAL;
    /*!
     * \brief SAMPLE
     * nmon total sample
     */
    int SAMPLE;
    /*!
     * \brief initAction
     * install applications
     * ,read ini file
     * \return
     */
    int initAction();
    /*!
     * \brief clientAction
     * look for client information
     * , continue only we can find client reference
     * \return
     */
    bool clientAction();
    /*!
     * \brief ioZone3Action
     * run ionzone to check I/O
     */
    void ioZone3Action();
    /*!
     * \brief nmonAction
     *  run nomon
     * \return
     */
    bool nmonAction();
    /*!
     * \brief ventapDBBackupAction
     * Backup audit db and main db
     */
    void ventapDBBackupAction();
    /*!
     * \brief doneAction
     * zip and delete tmp files
     */
    void doneAction();
    /*!
     * \brief dbTest
     * test db
     */
    void dbTest();
    /*!
     * \brief verifyDB
     */
    void verifyDB();
    /*!
     * \brief fixDB
     * \param type 0->main db
     * ,1-> audit db
     */
    void fixDB(int type);
};

#endif // ANALYSER_H
