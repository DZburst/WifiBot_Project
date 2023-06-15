#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QSlider>
#include <QUrl>
#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Mise à jour de la vitesse sur l'écran LCD du GUI en fonctino de la position du Slider
    connect(ui->SetSpeed, &QSlider::valueChanged, this, [this](int speed)
            {
                updateSpeed(speed) ;
            }) ;

    // Création d'un timer permettant ensuite de mettre à jour chaque seconde les valeurs de la batterie ainsi que de la distance IR
    QTimer* timer = new QTimer(this) ;
    connect(timer, &QTimer::timeout, this, [this]()
            {
                updateBatteryLevel(robot.readBatteryLevel()) ;
                updateLeftIR(robot.readLeftIR()) ;
                updateRightIR(robot.readRightIR()) ;
            }) ;
    timer->start(1000) ;

    // Création d'un objet manager pour gérer le réseau
    manager = new QNetworkAccessManager(this);
    // Création de la vue de la caméra
    QWebEngineView *view = new QWebEngineView();
    // Charger l'URL de la caméra dans la vue
    view->load(QUrl("http://192.168.1.106:8080/?action=stream"));
    view->show();
    //Ajouterla vue à un conteneur dans l'interface utilisateur
    this->ui->cam->addWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//gérer les évenement de clavier

    //lorsqu'une touche du clavier est enfoncée
void MainWindow::keyPressEvent(QKeyEvent* key_robot){
    switch(key_robot->key()){
    case Qt::Key_Z :    // Avancer
        robot.moveForward(robot.getSpeed());
        break;
    case Qt::Key_Q :    // Gauche
        robot.moveLeft(robot.getSpeed());
        break;
    case Qt::Key_D :    // Droite
        robot.moveRight(robot.getSpeed());
        break;
    case Qt::Key_S :    // Reculer
        robot.moveBackward(robot.getSpeed());
        break;
    }
}
    //lorsqu'une touche du clavier est relachée
void MainWindow::keyReleaseEvent(QKeyEvent* key_robot){
    robot.moveStop();
}

// relier la connection à l'interface
void MainWindow::on_Connect_clicked()
{
    robot.doConnect() ;
    robot.setConnection(1) ;
}

// relier la déconnection à l'interface
void MainWindow::on_Disconnect_clicked()
{
    robot.disConnect();
}

// relier les mouvements à l'interface
    //avancer
void MainWindow::on_Up_Arrow_clicked()
{
    robot.moveForward(robot.getSpeed()) ;
}

    //droite
void MainWindow::on_Right_Arrow_clicked()
{
    robot.moveRight(robot.getSpeed()) ;
}

    //gauche
void MainWindow::on_Down_Arrow_clicked()
{
    robot.moveBackward(robot.getSpeed()) ;
}

    //reculer
void MainWindow::on_Left_Arrow_clicked()
{
    robot.moveLeft(robot.getSpeed()) ;
}

    //arrêter
void MainWindow::on_STOP_clicked()
{
    robot.moveStop() ;
}


//envoyer une requête HTTP à l'URL "http://192.168.1.106:8080" pour effectuer une fonction spécifique selon les paramétres pour contrôler la caméra
    //haut
void MainWindow::cam_haut(){
request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=l&value=-200"));
manager->get(request);
}


    //bas
void MainWindow::cam_bas()
{
request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200"));
    //envoyer une requête get au manager pour effectuer le déplacement
manager->get(request);
}


    //gauche
void MainWindow::cam_gauche()
{
request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200"));
manager->get(request);
}


   //droite
void MainWindow::cam_droite()
{
request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200"));
manager->get(request);
}


// relier la camera a l'interface
void MainWindow::on_Camera_Up_clicked()
{
    cam_haut();
}


void MainWindow::on_Camera_Right_clicked()
{
    cam_droite();
}


void MainWindow::on_Camera_Down_clicked()
{
    cam_bas();
}


void MainWindow::on_Camera_Left_clicked()
{
    cam_gauche();
}


// changer la vitesse sur le GUI
void MainWindow::updateSpeed(int speed)
{
    robot.setSpeed(speed) ;
    ui->SpeedLCD->display(speed) ;
}

// changer la batterie sur le GUI
void MainWindow::updateBatteryLevel(int battery_level)
{
    robot.setBatteryLevel(battery_level) ;
    ui->Battery_Level->setRange(0, 100) ;
    ui->Battery_Level->setValue(battery_level) ;
}


// changer la distance IR gauche sur le GUI
void MainWindow::updateLeftIR(int distance)
{
    robot.setLeftIR(distance) ;
    ui->LeftIRLCD->display(distance) ;
}


// changer la distance IR droite sur le GUI
void MainWindow::updateRightIR(int distance)
{
    robot.setRightIR(distance) ;
    ui->RightIRLCD->display(distance) ;
}

