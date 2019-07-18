#ifndef FILEHANDLERCREATOR_H
#define FILEHANDLERCREATOR_H
#include<QString>
#include<QObject>

class FileHandlerCreator
{
private:
    FileHandlerCreator();
    volatile static FileHandlerCreator fileHandler;
    static QString DATE_FORMAT;

public:
    static FileHandlerCreator getFileHandler(QString pattern);
};
#endif // FILEHANDLERCREATOR_H
