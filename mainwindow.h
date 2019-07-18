#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
signals:
    void loginSignal();

private slots:
    bool loginBtnClicked();
    void exitBtnClicked();
    void start();
    void done();
};

#endif // MAINWINDOW_H
