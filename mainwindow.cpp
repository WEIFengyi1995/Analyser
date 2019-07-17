#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loginBtnClicked(){
    QString name=this->ui->username->text();
    QString password=this->ui->password->text();
    if(name==""||name.isNull()){
        QMessageBox::information(this,"","Please input username.");
        return false;
    }
    if(password==""||password.isNull()){
        QMessageBox::information(this,"","Please input password.");
        return false;
    }
    if(name=="arcsolu"&&password=="analyser"){
        QMessageBox::information(this,"","Start writting logs...");
        return true;
    }
    QMessageBox::information(this,"","Wrong username or wrong password.");
    return false;
}

void MainWindow::exitBtnClicked(){
    this->close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->exit, SIGNAL(clicked()),this,SLOT(exitBtnClicked()));
    connect(ui->Login,SIGNAL(clicked()),this,SLOT(loginBtnClicked()));
}
