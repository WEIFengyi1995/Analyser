#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loginBtnClicked(){

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
}
