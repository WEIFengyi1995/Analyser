#include"tool.h"
#include <QDebug>
#include <QTextStream>

bool cutFile(QString old , QString des,int n,int length,QString &error ){
    QFile file(old);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<old<<" can not open : "  <<file.errorString();
        error=old+"  can not open : "+  file.errorString();
        return  false ;
    }

    QTextStream out(&file);
    QStringList info1;
    QStringList info;

    QString useful;

    while(out.readLineInto(&useful)){
        if(useful.contains(",T00"))
            info1<<useful;
    }
    file.close();

    for(int i=0;i<info1.size();i++){
        QString ori=info1.at(i);
        int idx=ori.indexOf(",T00");
        int number=ori.mid(idx+2,4).toInt();
        number=number+length*n;
        QString newNumber=QString("%1").arg(number,4,10,QLatin1Char('0'));
        ori.replace(idx,6,",T"+newNumber);
        info<<ori;

    }

    QFile destination(des);
    if(!destination.open(QIODevice::ReadWrite| QIODevice::Append)){
        qDebug()<<des<<" can not open : "  <<destination.errorString();
        error=des+"  can not open : "+  destination.errorString();
        return false;
    }
    QTextStream in(&destination);
    for(int i=0;i<info.size();i++){
        in<<info.at(i)<<"\n";
    }
    destination.close();
    return true;
}





QFile* create(QString filename,QString &error){
    QFile file(filename);
    QFile * f1=&file;
    if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate)){
        error=file.errorString();
        qDebug()<<file.errorString();
    }
    return f1;
}
