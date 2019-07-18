#ifndef ANALYSER_H
#define ANALYSER_H
#include "service.h"

class Analyser:public Service

{
public:
    void start();
    static Analyser *getAnalyser();

private:
    static Analyser *instance;
    Analyser();
    void initAction();
    void clientAction();
    void ioZone3Action();
    void nmonAction();
    void doneAction();
};

#endif // ANALYSER_H
