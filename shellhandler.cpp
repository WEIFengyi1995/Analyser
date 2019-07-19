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

    proc->waitForFinished();
    return proc->exitCode();
}

int ShellHandler::doShell(QString cmd){
    qDebug()<<cmd;
    int code = proc->execute(cmd);
    return code;
}

void ShellHandler::handProcError(QProcess::ProcessError error){
    qDebug()<<error;
    //exit(0);
}
