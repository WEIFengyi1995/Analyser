#ifndef LANGUAGE_H
#define LANGUAGE_H


 #include <QMap>

class language
{
public:
    language();
    const static QMap<QString,QString> config;
    const static QMap<QString,QString> info;
    const static QMap<QString,QString> warning;
    const static QMap<QString,QString> severe;
};

#endif // LANGUAGE_H
