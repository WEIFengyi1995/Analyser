#ifndef LOGGER_H
#define LOGGER_H
#include <QFile>
#include <QObject>
#define COLOR_CONFIG "\033[34;1m"
#define COLOR_WARNNING "\033[33;1m"
#define COLOR_INFO "\033[32;1m"
#define COLOR_SEVERE "\033[31;1m"
#define COLOR_RESET "\033[0m"


class Logger:public QObject
{
    Q_OBJECT
public:
    Logger();
    /*!
      print logger to file
     * @brief setFile
     * @param file
     */
    void setFile(QString file);
    ~Logger();
public slots:
    /*!

     * \brief info_log
     *  type [info]
     * \param action
     * \param info
     */
    void info_log(QString action,QString info);
    /*!

     * \brief warning_log
     * type[warning]
     * \param action
     * \param warning
     */
    void warning_log(QString action,QString warning );
    /*!
     * \brief severe_log
     * type[severe]
     * \param action
     * \param severe
     */
    void severe_log(QString action,QString severe);
    /*!
     * \brief config_log
     * type[config]
     * \param action
     * \param config
     */
    void config_log(QString action,QString config );


signals:
    /*!
     * \brief error
     * error messages
     * \param error
     */
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
