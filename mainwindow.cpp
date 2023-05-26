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
    robot.doConnect() ;
}


void MainWindow::on_Disconnect_clicked()
{
    robot.disConnect();
}


void MainWindow::on_Up_Arrow_pressed()
{
    robot.moveForward(robot.getSpeed(), robot.getSpeed()) ;
}


void MainWindow::on_Right_Arrow_pressed()
{
    robot.moveRight(robot.getSpeed()) ;
}


void MainWindow::on_Down_Arrow_pressed()
{
    robot.moveBackward(robot.getSpeed(), robot.getSpeed()) ;
}


void MainWindow::on_Left_Arrow_pressed()
{
    robot.moveLeft(robot.getSpeed()) ;
}


void MainWindow::on_SetSpeed_sliderMoved(int speed)
{
    robot.setSpeed(speed) ;
}


void MainWindow::on_Up_Arrow_released()
{
    robot.setSpeed(0) ;
}


void MainWindow::on_Right_Arrow_released()
{
    robot.setSpeed(0) ;
}


void MainWindow::on_Down_Arrow_released()
{
    robot.setSpeed(0) ;
}


void MainWindow::on_Left_Arrow_released()
{
    robot.setSpeed(0) ;
}


