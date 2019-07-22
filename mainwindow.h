#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "service.h"
#include <QStandardItemModel>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringList strList;
    QStandardItemModel * standardItemModel;
signals:
    void loginSignal();
    void continueSignal();
    void restartSignal();
private slots:
    bool loginBtnClicked();
    void exitBtnClicked();
    void closeBtnClicked();
    void done(QString error);
    void runCloseBtnClicked();
    void recvInfo(QString action,QString info);
    void continueBtnClicked();
    void recheckBtnClicked();
};

#endif // MAINWINDOW_H
