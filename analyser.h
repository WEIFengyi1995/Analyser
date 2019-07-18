#ifndef ANALYSER_H
#define ANALYSER_H
#include "service.h"
#include "shellhandler.h"

class Analyser:public Service

{

public:
    void start();
    static Analyser *getAnalyser();
    ~Analyser();


private:
    static Analyser *instance;
    Analyser();
    void initAction();
    void clientAction();
    void ioZone3Action();
    void nmonAction();
    void ventapDBBackupAction();
    void doneAction();
    ShellHandler * shell;


};

#endif // ANALYSER_H
