#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Connect_clicked()
{
    robot.doConnect();
}


void MainWindow::on_Disconnect_clicked()
{
    robot.disConnect();
}

void MainWindow::on_Up_Arrow_clicked()
{
    robot.moveForward() ;
}


void MainWindow::on_Left_Arrow_clicked()
{
    robot.moveLeft() ;
}


void MainWindow::on_Right_Arrow_clicked()
{
    robot.moveRight() ;
}

void MainWindow::on_Down_Arrow_clicked()
{
    robot.moveBackward() ;
}


