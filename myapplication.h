#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H
#include <QApplication>
#include <QThread>



class MyApplication: public QApplication
{
public:
    MyApplication(int &argc, char ** garv);

    static QThread *getThread();

private:
    static QThread *t;

};

#endif // MYAPPLICATION_H
