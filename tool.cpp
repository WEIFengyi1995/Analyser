#include"tool.h"
#include <QDebug>
#include <QTextStream>


QFile* create(QString filename,QString &error){
    QFile file(filename);
    QFile * f1=&file;
    if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate)){
        error=file.errorString();
        qDebug()<<file.errorString();
    }
    return f1;
}
