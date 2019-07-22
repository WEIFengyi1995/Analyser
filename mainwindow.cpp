#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTime>
MainWindow::~MainWindow()
{
    delete ui;
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
    QMessageBox::information(this,"Attention","Please don't close your computer until the inspection is done.");
    this->hide();
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
        QApplication::setQuitOnLastWindowClosed(false);
        ui->Login->setEnabled(false);
        ui->exit->setEnabled(false);
        ui->username->setEnabled(false);
        ui->password->setEnabled(false);
        ui->widget->hide();
        ui->completWidget->hide();
        ui->runWidget->show();
       /* QTime dieTime=QTime::currentTime().addSecs(1);
        while( QTime::currentTime() < dieTime ){
<<<<<<< HEAD
             QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }*/
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
    QTime dieTime=QTime::currentTime().addSecs(2);
    while( QTime::currentTime() < dieTime ){
         QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
    }
    if(error.isNull()||error==""){
        ui->errorText->clear();
    }else{
        ui->errorText->setText(error);
    }
    this->show();
    ui->widget->hide();
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
    ui->runWidget->hide();
    ui->completWidget->hide();
    ui->widget->show();
    connect(ui->exit, SIGNAL(clicked()),this,SLOT(exitBtnClicked()));
    connect(ui->closeButton, SIGNAL(clicked()),this,SLOT(closeBtnClicked()));
    connect(ui->Login,SIGNAL(clicked()),this,SLOT(loginBtnClicked()));
    connect(ui->runCloseButton,SIGNAL(clicked()),this,SLOT(runCloseBtnClicked()));
}
