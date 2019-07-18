#include "shellhandler.h"
#include <QDebug>

ShellHandler::ShellHandler()
{
    this->proc = new QProcess();
    QObject::connect(proc,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(handProcError(QProcess::ProcessError)));
}

int ShellHandler::doShell(QString cmd, QString output){
    if(!output.isEmpty()){
        proc->setStandardOutputFile(output);
    }
    proc->start(cmd);
    proc->waitForFinished();
    if(proc->exitCode() != 0){
    }
    return proc->exitCode();
}

int ShellHandler::doShell(QString cmd){
    int code = proc->execute(cmd);
    return code;
}
void ShellHandler::handProcError(QProcess::ProcessError error){
    qDebug()<<error;
    //exit(0);
}
