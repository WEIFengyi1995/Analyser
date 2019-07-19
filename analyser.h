#ifndef ANALYSER_H
#define ANALYSER_H
#include "service.h"
#include "shellhandler.h"
#include "dbconnector.h"
#include "logger.h"

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
    int initAction();
    bool clientAction();
    void ioZone3Action();
    void nmonAction();
    void ventapDBBackupAction();
    void doneAction();
    void dbTest();
    void verifyDB();
    void fixDB(int type);
    ShellHandler * shell = nullptr;
    Logger * log;


};

#endif // ANALYSER_H
