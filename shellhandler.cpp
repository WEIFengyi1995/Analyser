#include "shellhandler.h"
#include "constantstools.h"
#include "myapplication.h"
#include <QDebug>

ShellHandler::ShellHandler()
{
    this->proc = new QProcess();
    proc->moveToThread(MyApplication::getThread());
    //proc->moveToThread(QCoreApplication::instance()->thread());
    //QObject::connect(proc,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(handProcError(QProcess::ProcessError)));
}

int ShellHandler::doShell(QString cmd, QString output){
    //QProcess proc1;
    if(!output.isEmpty()){
        proc->setStandardOutputFile(output);
    }
    proc->start(cmd);
    proc->waitForFinished(constantsTools::DAY);
    proc->close();
    proc->setStandardOutputFile("");
    return proc->exitCode();
    //return proc1.execute(cmd);
}

int ShellHandler::doShell(QString cmd){
    //QProcess proc1;
    int code = proc->execute(cmd);
    return code;
}
