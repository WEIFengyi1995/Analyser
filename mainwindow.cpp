#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTime>
#include "constantstools.h"
#include <QDir>
#include <QDebug>

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::continueBtnClicked(){
    QApplication::setQuitOnLastWindowClosed(false);
    ui->Login->setEnabled(false);
    ui->exit->setEnabled(false);
    ui->username->setEnabled(false);
    ui->password->setEnabled(false);
    ui->loginWidget->hide();
    ui->completWidget->hide();
    ui->crashWidget->hide();
    ui->runWidget->show();
    //todo
    emit continueSignal();
}

void MainWindow::recheckBtnClicked(){
    ui->crashWidget->hide();
    ui->runWidget->show();
    emit loginSignal();
}

void MainWindow::recvInfo(QString action, QString info){
    QString line;
    if(action==""){
        line=info;
    }else{
        line=action+" "+info;
    }
    standardItemModel=new QStandardItemModel(this);
    strList.append(line);
    int nCount=strList.size();
    for(int i=0;i<nCount;i++){
        QString string=static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(string);
        item->setBackground(Qt::white);
        standardItemModel -> appendRow(item);
    }
    ui->infoList->setModel(standardItemModel);
}


void MainWindow::runCloseBtnClicked(){
    QMessageBox::information(this,"请注意","检查在后台运行，请检查结束前不要关闭电脑，谢谢.");
    this->hide();
}

bool MainWindow::loginBtnClicked(){
    QString name=this->ui->username->text();
    QString password=this->ui->password->text();
    if(name==""||name.isNull()){
        QMessageBox::information(this,"","请输入用户名.");
        return false;
    }
    if(password==""||password.isNull()){
        QMessageBox::information(this,"","请输入密码.");
        return false;
    }
    if(name=="*"&&password=="*"){
        QApplication::setQuitOnLastWindowClosed(false);
        ui->Login->setEnabled(false);
        ui->exit->setEnabled(false);
        ui->username->setEnabled(false);
        ui->password->setEnabled(false);
        ui->loginWidget->hide();
        ui->completWidget->hide();

        if(newService){
             ui->runWidget->show();
             emit loginSignal();
        }else{
             ui->crashWidget->show();
        }
        return true;
    }
    QMessageBox::information(this,"","密码或用户名错误.");
    return false;
}

void MainWindow::exitBtnClicked(){
    this->close();
}


void MainWindow::done(QString error){
    /*QTime dieTime=QTime::currentTime().addSecs(2);
    while( QTime::currentTime() < dieTime ){
         QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
    }*/
    if(error.isNull()||error==""){
        ui->errorText->clear();
    }else{
        ui->errorText->setText(error);
    }
    this->show();
    ui->loginWidget->hide();
    ui->runWidget->hide();
    ui->completWidget->show();
    QApplication::setQuitOnLastWindowClosed(true);
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
    ui->errorText->adjustSize();
    ui->errorText->setGeometry(QRect(10,70,251,27*4));
    ui->errorText->setWordWrap(true);
    ui->errorText->setAlignment(Qt::AlignLeft);
    bool tmp = !QDir(constantsTools::PATH_TMP).exists();
    qDebug()<<constantsTools::PATH_TMP;
    qDebug()<<tmp;
    if (tmp){
        newService=true;
    }else{
        newService=false;
    }
    ui->runWidget->hide();
    ui->crashWidget->hide();
    ui->completWidget->hide();
    ui->loginWidget->show();

    connect(ui->exit, SIGNAL(clicked()),this,SLOT(exitBtnClicked()));
    connect(ui->closeButton, SIGNAL(clicked()),this,SLOT(closeBtnClicked()));
    connect(ui->Login,SIGNAL(clicked()),this,SLOT(loginBtnClicked()));
    connect(ui->runCloseButton,SIGNAL(clicked()),this,SLOT(runCloseBtnClicked()));
    connect(ui->continueButton, SIGNAL(clicked()),this,SLOT(continueBtnClicked()));
    connect(ui->recheckButton, SIGNAL(clicked()),this,SLOT(recheckBtnClicked()));


}
