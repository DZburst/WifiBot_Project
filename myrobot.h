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
    void setConnection(bool connected) ;
    void setBatteryLevel(int battery_level) ;
    int getSpeed() ;
    bool getConnection() ;
    int getBatteryLevel() ;
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
    void moveBackward(int speed) ;
    void moveForward(int speed) ;
    void moveRight(int speed) ;
    void moveLeft(int speed) ;
    void moveStop() ;
    int readBatteryLevel() ;


private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
    int robot_speed = 0 ;
    bool is_connected ;
    int battery_level ;
};

#endif // MYROBOT_H
