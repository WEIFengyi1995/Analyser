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
    int  getnmonPid();
private:
    QProcess *proc;
    int nmonPid;
public slots:
    void readStdout();
};

#endif // SHELLHANDLER_H
