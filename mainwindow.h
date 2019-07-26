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
    bool newService;

signals:
    /*!
     * \brief loginSignal emit when login successful
     */
    void loginSignal();

private slots:
    /*!
     * \brief loginBtnClicked
     * login action
     * \return
     */
    bool loginBtnClicked();
    /*!
     * \brief exitBtnClicked
     * quit the program
     */
    void exitBtnClicked();
    /*!
     * \brief closeBtnClicked
     */
    void closeBtnClicked();
    /*!
     * \brief done
     * \param error
     */
    void done(QString error);
    /*!
     * \brief runCloseBtnClicked
     * hide ui and keeping running the program
     */
    void runCloseBtnClicked();
    /*!
     * \brief recvInfo display information on ui
     * \param action
     * \param info
     */
    void recvInfo(QString action,QString info);

    /*!
     * \brief recheckBtnClicked
     * click to restart the program
     */

    void recheckBtnClicked();
    /*!
     * \brief NmonProcess update value of processbar
     */
    void NmonProcess(int);
};

#endif // MAINWINDOW_H
