#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QSlider>
#include <QVBoxLayout>
// #include <QWebEngineView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(robot.getBatteryLevel())
    {
        connect(ui->SetSpeed, &QSlider::valueChanged, this, [this](int speed)
        {
            updateSpeed(speed) ;
        }) ;

        QTimer* timer = new QTimer(this) ;
        connect(timer, &QTimer::timeout, this, [this]()
        {
            updateBatteryLevel(robot.readBatteryLevel()) ;
            qDebug() << robot.getBatteryLevel() ;
        }) ;
        timer->start(1000) ;

        /*
        // Création de la vue de la caméra
        QWebEngineView *view = new QWebEngineView();

        //QVBoxLayout *layout = new QVBoxLayout(ui->cameraWidget);
        //layout->addWidget(view);
        view->load(QUrl("http://192.168.1.106:8080/?action=stream"));
        view->resize(100,100);
        this->ui->formLayout_2->addWidget(view);
        this->ui->formLayout_2->geometry().setHeight(100);
        this->ui->formLayout_2->geometry().setWidth(100);

        view->show();
        */
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Connect_clicked()
{
    robot.doConnect() ;
    robot.setConnection(1) ;
}


void MainWindow::on_Disconnect_clicked()
{
    robot.disConnect();
}


void MainWindow::on_Up_Arrow_clicked()
{
    robot.moveForward(robot.getSpeed()) ;
}


void MainWindow::on_Right_Arrow_clicked()
{
    robot.moveRight(robot.getSpeed()) ;
}


void MainWindow::on_Down_Arrow_clicked()
{
    robot.moveBackward(robot.getSpeed()) ;
}


void MainWindow::on_Left_Arrow_clicked()
{
    robot.moveLeft(robot.getSpeed()) ;
}


void MainWindow::updateSpeed(int speed)
{
    robot.setSpeed(speed) ;
    ui->SpeedLCD->display(speed) ;
}


void MainWindow::updateBatteryLevel(int battery_level)
{
    robot.setBatteryLevel(battery_level) ;
    ui->Battery_Level->setRange(0, 100) ;
    ui->Battery_Level->setValue(battery_level) ;
}

