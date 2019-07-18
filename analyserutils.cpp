#include "analyserutils.h"

int doShell(QString cmd,QString output){
    QProcess proc;
    if(!output.isEmpty()){
        proc.setStandardOutputFile(output);
    }
    proc.start(cmd);
    proc.waitForFinished();
    proc.close();
    return proc.exitCode();

}
