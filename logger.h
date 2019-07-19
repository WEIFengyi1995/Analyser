#ifndef LOGGER_H
#define LOGGER_H
#include <QFile>
#include <QObject>
#define COLOR_CONFIG "\033[32;1m"
#define COLOR_WARNNING "\033[35m"
#define COLOR_INFO "\033[31;1m"
#define COLOR_SEVERE "\033[34m"
#define COLOR_RESET "\033[0m"


class Logger:public QObject
{
    Q_OBJECT
public:
    Logger();
    void setFile(QString file);
    ~Logger();
public slots:
    void info_log(QString action,QString info);
    void warning_log(QString action,QString warning );
    void severe_log(QString action,QString severe);
    void config_log(QString action,QString config );
signals:
    void error(QString error);

private:
    QFile *file;
    QString FileName;
    QString DATE_FORMAT="dddd dd/MM/yyyy HH:mm:ss.zzz";
    void info(QString action,QString info);
    void warning(QString action,QString warning);
    void severe(QString action,QString severe);
    void config(QString action,QString config);

};

#endif // LOGGER_H
