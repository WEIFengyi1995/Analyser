#ifndef ANALYSER_H
#define ANALYSER_H
#include "service.h"
#include "shellhandler.h"
#include "dbconnector.h"

class Analyser:public Service
{
    Q_OBJECT

public:
    static Analyser *getAnalyser();
    ~Analyser();

signals:
   void start_Error(QString error);

public slots:
    void start();

private:
    static Analyser *instance;
    Analyser();
    int initAction();
    void clientAction();
    void ioZone3Action();
    void nmonAction();
    void ventapDBBackupAction();
    void doneAction();
    ShellHandler * shell=nullptr;




};

#endif // ANALYSER_H
