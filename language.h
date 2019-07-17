#ifndef LANGUAGE_H
#define LANGUAGE_H


 #include <QMap>

class language
{
public:
    language();
    const QMap<QString,QString> config;
    const QMap<QString,QString> info;
    const QMap<QString,QString> warning;
    const QMap<QString,QString> severe;
};

#endif // LANGUAGE_H
