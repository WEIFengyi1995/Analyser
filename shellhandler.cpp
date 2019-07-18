#include "shellhandler.h"

ShellHandler::ShellHandler()
{
    this->proc = new QProcess();
    QObject::connect(this->proc,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(handProcError(QProcess::ProcessError)));
}

int ShellHandler::doShell(QString cmd, QString output){
    if(!output.isEmpty()){
        proc->setStandardOutputFile(output);
    }
    proc->start(cmd);
    proc->waitForFinished();
    if(proc->exitCode() != 0){

    }
}

void ShellHandler::handProcError(QProcess::ProcessError error){
    exit(0);
}
