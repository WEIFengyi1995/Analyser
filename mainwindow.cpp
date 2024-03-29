#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "constantstools.h"
#include <QDir>
#include <QDebug>
#include <QAbstractItemView>
#include <QShortcut>

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NmonProcess(int percent){
    this->ui->progressBar->setValue(percent);
}

void MainWindow::recheckBtnClicked(){
    newService=true;
    ui->recheckButton->setEnabled(false);
    ui->crashWidget->hide();
    ui->loginWidget->hide();
    ui->runWidget->hide();
    ui->completWidget->hide();
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
    ui->infoList->scrollToBottom();

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
    if(name=="arcsolu"&&password=="analyser"){
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
    //this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint);
    this-> setWindowFlags(windowFlags()&~ (Qt::WindowMinMaxButtonsHint));
    this->setFixedSize(392,481);
    ui->errorText->adjustSize();
    ui->errorText->setGeometry(QRect(10,80,371,281));
    ui->errorText->setWordWrap(true);
    ui->errorText->setAlignment(Qt::AlignLeft);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(2);
    bool tmp = !QDir(constantsTools::PATH_TMP).exists();
    if (tmp){
        newService=true;
    }else{
        newService=false;
    }
    ui->runWidget->hide();
    ui->crashWidget->hide();
    ui->completWidget->hide();
    ui->loginWidget->show();
    QShortcut *key=new QShortcut(QKeySequence(Qt::Key_Return),ui->loginWidget);
    connect(ui->exit, SIGNAL(clicked()),this,SLOT(exitBtnClicked()));
    connect(ui->closeButton, SIGNAL(clicked()),this,SLOT(closeBtnClicked()));
    connect(ui->Login,SIGNAL(clicked()),this,SLOT(loginBtnClicked()));
    connect(ui->runCloseButton,SIGNAL(clicked()),this,SLOT(runCloseBtnClicked()));
    connect(ui->recheckButton, SIGNAL(clicked()),this,SLOT(recheckBtnClicked()));
    connect(key,SIGNAL(activated()),this,SLOT(loginBtnClicked()));
}
