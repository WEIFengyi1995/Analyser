#include "mainwindow.h"
#include <QApplication>
#include "service.h"
#include "analyser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Service *ser = Analyser::getAnalyser();
    ser->start();


    return a.exec();
}
