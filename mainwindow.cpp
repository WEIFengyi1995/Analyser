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
    if(name=="arcsolu"||password=="analyser"){
        ui->Login->setEnabled(false);
        ui->exit->setEnabled(false);
        ui->username->setEnabled(false);
        ui->password->setEnabled(false);
        ui->widget->hide();
        ui->completWidget->hide();
        ui->runWidget->show();
        emit loginSignal();
        return true;
    }
    QMessageBox::information(this,"","Wrong username or wrong password.");
    return false;
}

void MainWindow::exitBtnClicked(){
    this->close();
}


void MainWindow::done(QString error){
    if(error.isNull()||error==""){
        ui->errorText->clear();
    }else{
        ui->errorText->setText(error);
    }
    ui->widget->hide();
    ui->runWidget->hide();
    ui->completWidget->show();
}


void MainWindow::closeBtnClicked(){
    this->close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    ui->runWidget->hide();
    ui->completWidget->hide();
    ui->widget->show();
    connect(ui->exit, SIGNAL(clicked()),this,SLOT(exitBtnClicked()));
    connect(ui->closeButton, SIGNAL(clicked()),this,SLOT(closeBtnClicked()));
    connect(ui->Login,SIGNAL(clicked()),this,SLOT(loginBtnClicked()));
}
