#ifndef ANALYSER_H
#define ANALYSER_H
#include "service.h"
#include "shellhandler.h"
#include "dbconnector.h"
#include "logger.h"

class Analyser:public Service

{

public slots:
    void start();
public:
    static Analyser *getAnalyser(Logger &log);
    ~Analyser();


private:
    static Analyser *instance;
    Analyser(Logger &log);
    int initAction();
    void clientAction();
    void ioZone3Action();
    void nmonAction();
    void ventapDBBackupAction();
    void doneAction();
    ShellHandler * shell;
    Logger * log;


};

#endif // ANALYSER_H
