#ifndef ANALYSER_H
#define ANALYSER_H
#include "service.h"
#include "shellhandler.h"
#include "dbconnector.h"

class Analyser:public Service
{
    Q_OBJECT
public slots :
    void start();
public:
    static Analyser *getAnalyser();
    ~Analyser();


private:
    static Analyser *instance;
    Analyser();
    int initAction();
    void clientAction();
    void ioZone3Action();
    void nmonAction();
    void ventapDBBackupAction();
    void doneAction();
    ShellHandler * shell;

signals:
    void startError();


};

#endif // ANALYSER_H
