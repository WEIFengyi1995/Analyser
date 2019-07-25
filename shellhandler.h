#ifndef SHELLHANDLER_H
#define SHELLHANDLER_H
#include <QProcess>

class ShellHandler:QObject
{
    Q_OBJECT
public:
    ShellHandler();
    int doShell(QString cmd,QString output);
    int doShell(QString cmd);
    void doConnect();
    void doDeconnect();
    int  getnmonPid();
private:
    QProcess *proc;
    int nmonPid;
private slots:
    void readProcPid();
};

#endif // SHELLHANDLER_H
