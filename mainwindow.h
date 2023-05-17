
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myrobot.h"



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
    void on_Up_Arrow_clicked();

    void on_Left_Arrow_clicked();

    void on_Right_Arrow_clicked();

    void on_Down_Arrow_clicked();

    void on_Connect_clicked();

    void on_Disconnect_clicked();

private:
    Ui::MainWindow *ui ;
    MyRobot robot ;
};

#endif // MAINWINDOW_H
