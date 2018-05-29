#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    h_limit=1000;
    v_limit=500;
    dt=0.02;                            //Asigna el lapso de tiempo

    timer=new QTimer(this);                 //crea el timer
    scene=new QGraphicsScene(this);         //crea la scene
    scene->setSceneRect(0,0,h_limit,v_limit);     //asigna el rectangulo que encierra la scene, determinado por h_limit y v_limit

    ui->graphicsView->setScene(scene);
            qDebug()<<ui->graphicsView->size();
    ui->centralWidget->adjustSize();
            qDebug()<<ui->centralWidget->size();


        qDebug()<<this->size();
    scene->addRect(scene->sceneRect());

    timer->stop();                              //para el timer
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));


}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete ui;
}

void MainWindow::actualizar()
{
    for(int i=0;i<bars.size();i++){
        bordercollision(bars.at(i)->getEsf());
        bars.at(i)->actualizar(dt,v_limit);



    }
}

void MainWindow::bordercollision(EsferaSim *b)
{
    if(b->getX()< b->getR() || b->getX()>h_limit-b->getR()){
        b->setVel(b->get_e()*b->getVx(),b->getVy());
    }
    if(b->getY()<1.0*b->getR()){
        b->setVel(b->getVx(),b->get_e()*b->getVy());
    }
    else if(b->getY() > v_limit -(b->getR())){
        b->setVel(b->getVx(),-1*b->getVy());
    }
    if(b->getY()<1.0*b->getR()){
        b->setY(b->getR());
    }

}



void MainWindow::on_pushButton_clicked()
{
     timer->start(1000*dt);
}


void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    int x,y,vel,radio;
    x=rand() % 980 + 2;
    y= rand() % 480 + 2;
    radio= rand() % 25 + 5;
    vel= rand() % 295 + 5;
    bars.append(new EsferaGraf(x,y,radio));
    bars.last()->getEsf()->setVel(vel,vel);
    for(int i=0;i<bars.size();i++){
        bars.at(i)->actualizar(dt,v_limit);
        scene->addItem(bars.at(i));
}
    }
