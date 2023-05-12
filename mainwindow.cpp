#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    robot.doConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}


short Crc16(unsigned char *Adresse_tab , unsigned char Taille_max)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity= 0;
    Crc = 0xFFFF;
    Polynome = 0xA001;
    for ( CptOctet= 0 ; CptOctet < Taille_max ; CptOctet++)
    {
        Crc ^= *( Adresse_tab + CptOctet);
        for ( CptBit = 0; CptBit <= 7 ; CptBit++)
        {
            Parity= Crc;
            Crc >>= 1;
            if (Parity%2 == true) Crc ^= Polynome;
        }
    }
    return(Crc);
}


void MainWindow::on_Up_Arrow_clicked()
{
    robot.DataToSend[0] = 255 ;
    robot.DataToSend[1] = 7 ;
    robot.DataToSend[2] = 120 ;
    robot.DataToSend[3] = 0 ;
    robot.DataToSend[4] = 120 ;
    robot.DataToSend[5] = 0 ;
    robot.DataToSend[6] = 80 ;
    for (int i = 0 ; i < 8 ; i++)
        robot.DataToSend[7] += Crc16(robot.DataToSend, robot.DataToSend.length())[i] ;
    for (int j = 8 ; j < 16 ; j++)
        robot.DataToSend[8] = Crc16(robot.DataToSend, robot.DataToSend.length())[j] ;
}


void MainWindow::on_Left_Arrow_clicked()
{
    robot.DataToSend[0] = 255 ;
    robot.DataToSend[1] = 7 ;
    robot.DataToSend[2] = 120 ;
    robot.DataToSend[3] = 0 ;
    robot.DataToSend[4] = 0 ;
    robot.DataToSend[5] = 0 ;
    robot.DataToSend[6] = 64 ;
    for (int i = 0 ; i < 8 ; i++)
        robot.DataToSend[7] += Crc16(robot.DataToSend, robot.DataToSend.length())[i] ;
    for (int j = 8 ; j < 16 ; j++)
        robot.DataToSend[8] = Crc16(robot.DataToSend, robot.DataToSend.length())[j] ;
}


void MainWindow::on_Right_Arrow_clicked()
{
    robot.DataToSend[0] = 255 ;
    robot.DataToSend[1] = 7 ;
    robot.DataToSend[2] = 0 ;
    robot.DataToSend[3] = 0 ;
    robot.DataToSend[4] = 120 ;
    robot.DataToSend[5] = 0 ;
    robot.DataToSend[6] = 16 ;
    for (int i = 0 ; i < 8 ; i++)
        robot.DataToSend[7] += Crc16(robot.DataToSend, robot.DataToSend.length())[i] ;
    for (int j = 8 ; j < 16 ; j++)
        robot.DataToSend[8] = Crc16(robot.DataToSend, robot.DataToSend.length())[j] ;
}


void MainWindow::on_Down_Arrow_clicked()
{
    robot.DataToSend[0] = 255 ;
    robot.DataToSend[1] = 7 ;
    robot.DataToSend[2] = 120 ;
    robot.DataToSend[3] = 0 ;
    robot.DataToSend[4] = 120 ;
    robot.DataToSend[5] = 0 ;
    robot.DataToSend[6] = 0 ;
    for (int i = 0 ; i < 8 ; i++)
        robot.DataToSend[7] += Crc16(robot.DataToSend, robot.DataToSend.length())[i] ;
    for (int j = 8 ; j < 16 ; j++)
        robot.DataToSend[8] = Crc16(robot.DataToSend, robot.DataToSend.length())[j] ;
}
