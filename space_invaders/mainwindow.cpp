#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene), vaisseau_joueur(new Vaisseau), tir_joueur(new Projectile)
{
    ui->setupUi(this);
    scene->setSceneRect(-300, -300, 600, 600);
    scene->addItem(vaisseau_joueur);
    scene->addItem(tir_joueur);
    ui->graphicsView->setScene(scene);
    tir_joueur->hide();
    }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Q:
        qDebug("Gauche");
        vaisseau_joueur->bouge_gauche();
        break;
    case Qt::Key_D:
        qDebug("Droite");
        vaisseau_joueur->bouge_droite();
        break;
    case Qt::Key_Space:
        qDebug("pioupioupiou");
        tir_joueur->show();
        tir_joueur->set_position(vaisseau_joueur->transfert_position());
        tir_joueur->projectile_move = true;



    }
}
