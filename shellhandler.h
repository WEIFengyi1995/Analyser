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
private:
    QProcess *proc;
private slots:
    void handProcError(QProcess::ProcessError error);
};

#endif // SHELLHANDLER_H
