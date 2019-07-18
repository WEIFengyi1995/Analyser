#ifndef LOGGER_H
#define LOGGER_H
#include <QFile>
#define COLOR_CONFIG "\033[32;1m"
#define COLOR_WARNNING "\033[33;1m"
#define COLOR_INFO "\033[31;1m"
#define COLOR_SEVERE "\033[33;1m"
#define COLOR_RESET "\033[0m"

class Logger
{
public:
    Logger(QString file);
    void info(QString info);
    void warning(QString warning);
    void severe(QString severe);
    void config(QString config);
private:
    QString FileName;
    QString DATE_FORMAT="dddd dd/MM/yyyy HH:mm:ss.zzz";

};

#endif // LOGGER_H
