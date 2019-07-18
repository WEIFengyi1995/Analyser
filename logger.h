#ifndef LOGGER_H
#define LOGGER_H
#include <QFile>
#include <QObject>
#define COLOR_CONFIG "\033[32;1m"
#define COLOR_WARNNING "\033[33;1m"
#define COLOR_INFO "\033[31;1m"
#define COLOR_SEVERE "\033[33;1m"
#define COLOR_RESET "\033[0m"


class Logger:public QObject
{
    Q_OBJECT
public:
    Logger(QString file);
    ~Logger();
public slots:
    void info_log(QString info);
    void warning_log(QString warning );
    void severe_log(QString severe);
    void config_log(QString config );


private:
    QFile *file;
    QString FileName;
    QString DATE_FORMAT="dddd dd/MM/yyyy HH:mm:ss.zzz";
    void info(QString info);
    void warning(QString warning);
    void severe(QString severe);
    void config(QString config);

};

#endif // LOGGER_H
