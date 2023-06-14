#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myrobot.h"
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QWebEngineView>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void Cam_Up();

    void Cam_Right();

    void Cam_Down();

    void Cam_Left();

    void on_Camera_Up_clicked();

    void on_Camera_Right_clicked();

    void on_Camera_Down_clicked();

    void on_Camera_Left_clicked();

    void on_Disconnect_clicked();

    void on_Up_Arrow_clicked();

    void on_Right_Arrow_clicked();

    void on_Down_Arrow_clicked();

    void on_Left_Arrow_clicked();

    void on_STOP_clicked();

    void on_Connect_clicked();

    void updateSpeed(int speed) ;

    void updateBatteryLevel(int battery_level) ;

private:
    Ui::MainWindow *ui ;
    MyRobot robot ;
    QWebEngineView *view;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
};

#endif // MAINWINDOW_H
