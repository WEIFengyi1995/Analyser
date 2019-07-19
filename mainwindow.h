#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "service.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Service *ser;
signals:
    void loginSignal();
private slots:
    bool loginBtnClicked();
    void exitBtnClicked();
    void closeBtnClicked();
    void start();
    void done();
};

#endif // MAINWINDOW_H
