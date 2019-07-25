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
    void start();

private:
    static Analyser *instance;
    Analyser(Logger &log);
    ShellHandler * shell = nullptr;
    Logger * log;
    int INTERVAL;
    int SAMPLE;
    int initAction();
    bool clientAction();
    void ioZone3Action();
    bool nmonAction();
    void ventapDBBackupAction();
    void doneAction();
    void dbTest();
    void verifyDB();
    void fixDB(int type);
};

#endif // ANALYSER_H
