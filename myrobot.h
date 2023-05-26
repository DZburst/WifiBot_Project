#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    void setSpeed(int speed) ;
    int getSpeed() ;
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();
    void moveBackward(int speed1, int speed2) ;
    void moveForward(int speed1, int speed2) ;
    void moveRight(int speed1) ;
    void moveLeft(int speed1) ;


private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
    int robot_speed ;
};

#endif // MYROBOT_H
