
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
    void cam_haut();
    void cam_bas();
    void cam_gauche();
    void cam_droite();

    void on_Disconnect_clicked();

    void on_Up_Arrow_clicked();

    void on_Right_Arrow_clicked();

    void on_Down_Arrow_clicked();

    void on_Left_Arrow_clicked();

    void on_STOP_clicked();

    void on_Connect_clicked();

    void updateSpeed(int speed) ;

    void updateBatteryLevel(int battery_level) ;

    void keyPressEvent(QKeyEvent* key_robot);
    void keyReleaseEvent(QKeyEvent* key_robot);

    void on_Camera_Up_clicked();

    void on_Camera_Right_clicked();

    void on_Camera_Down_clicked();

    void on_Camera_Left_clicked();

private:
    Ui::MainWindow *ui ;
    MyRobot robot ;

    QWebEngineView *view;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
};

#endif // MAINWINDOW_H
