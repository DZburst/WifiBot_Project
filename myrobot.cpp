#include "myrobot.h"
#include <iostream>

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
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
    for ( CptOctet= 1 ; CptOctet < Taille_max ; CptOctet++)
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

void MyRobot::moveBackward(){

    DataToSend[0] = 255 ;
    DataToSend[1] = 7 ;
    DataToSend[2] = 0;
    DataToSend[3] = 1;
    std::cout << DataToSend[3] << "\n" ;
    DataToSend[4] = 0;
    DataToSend[5] = 1;
    std::cout << DataToSend[5] << "\n" ;
    DataToSend[6] = 0;
    short crc = Crc16((unsigned char*)(DataToSend.data()), DataToSend.size()-2);
    DataToSend[7] = static_cast<unsigned char>(crc & 255);
    DataToSend[8] = static_cast<unsigned char>((crc >> 8) & 255);
    socket->write(DataToSend);
}

void MyRobot::moveForward(){

    DataToSend[0] = 255 ;
    DataToSend[1] = 7 ;
    DataToSend[2] = 0;
    DataToSend[3] = 1;
    std::cout << DataToSend[3] << "\n" ;
    DataToSend[4] = 0;
    DataToSend[5] = 1;
    std::cout << DataToSend[5] << "\n" ;
    DataToSend[6] = 80;
    short crc = Crc16((unsigned char*)(DataToSend.data()), DataToSend.size()-2);
    DataToSend[7] = static_cast<unsigned char>(crc & 255);
    DataToSend[8] = static_cast<unsigned char>((crc >> 8) & 255);
    socket->write(DataToSend);
}

void MyRobot::moveLeft(){

    DataToSend[0] = 255 ;
    DataToSend[1] = 7 ;
    DataToSend[2] = 0;
    DataToSend[3] = 1;
    std::cout << DataToSend[3] << "\n" ;
    DataToSend[4] = 0;
    DataToSend[5] = 0;
    std::cout << DataToSend[5] << "\n" ;
    DataToSend[6] = 64;
    short crc = Crc16((unsigned char*)(DataToSend.data()), DataToSend.size()-2);
    DataToSend[7] = static_cast<unsigned char>(crc & 255);
    DataToSend[8] = static_cast<unsigned char>((crc >> 8) & 255);
    socket->write(DataToSend);
}

void MyRobot::moveRight(){

    DataToSend[0] = 255 ;
    DataToSend[1] = 7 ;
    DataToSend[2] = 0;
    DataToSend[3] = 0;
    std::cout << DataToSend[3] << "\n" ;
    DataToSend[4] = 0;
    DataToSend[5] = 1;
    std::cout << DataToSend[5] << "\n" ;
    DataToSend[6] = 16;
    short crc = Crc16((unsigned char*)(DataToSend.data()), DataToSend.size()-2);
    DataToSend[7] = static_cast<unsigned char>(crc & 255);
    DataToSend[8] = static_cast<unsigned char>((crc >> 8) & 255);
    socket->write(DataToSend);
}

