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

    QNetworkAccessManager *manager = new QNetworkAccessManager () ;
    // Création de la vue de la caméra
    QWebEngineView *view = new QWebEngineView();
    view->load(QUrl("http://192.168.1.106:8080/?action=stream"));
    view->show();
    this->ui->cam->addWidget(view);

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


void MainWindow::on_STOP_clicked()
{
    robot.moveStop() ;
}


void MainWindow::Cam_Up(){
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=l&value=-200")) ;
    manager->get(request) ;
}


void MainWindow::Cam_Right()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")) ;
    manager->get(request) ;
}


void MainWindow::Cam_Down()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")) ;
    manager->get(request) ;
}


void MainWindow::Cam_Left()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")) ;
    manager->get(request) ;
}


void MainWindow::on_Camera_Up_clicked()
{
    Cam_Up() ;
}


void MainWindow::on_Camera_Right_clicked()
{
    Cam_Right() ;
}


void MainWindow::on_Camera_Down_clicked()
{
    Cam_Down() ;
}


void MainWindow::on_Camera_Left_clicked()
{
    Cam_Left() ;
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

