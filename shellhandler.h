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
};

#endif // SHELLHANDLER_H
