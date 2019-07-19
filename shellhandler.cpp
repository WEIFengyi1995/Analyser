#include "shellhandler.h"
#include <QDebug>

ShellHandler::ShellHandler()
{
    this->proc = new QProcess();
    QObject::connect(proc,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(handProcError(QProcess::ProcessError)));
}

int ShellHandler::doShell(QString cmd, QString output){
    //QProcess proc1;
    if(!output.isEmpty()){
        proc->setStandardOutputFile(output);
    }
    proc->start(cmd);
    proc->waitForFinished();
    //proc1.close();
    return proc->exitCode();
    //return proc1.execute(cmd);
}

int ShellHandler::doShell(QString cmd){
    //QProcess proc1;
    int code = proc->execute(cmd);
    return code;
}

void ShellHandler::handProcError(QProcess::ProcessError error){
    qDebug()<<error;
    //exit(0);
}
