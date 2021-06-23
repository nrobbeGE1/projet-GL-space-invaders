#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ennemi.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene),Ennemi{new ennemi(0, 1, 0), new ennemi(1, 1, 0), new ennemi(2, 1, 0), new ennemi(3,1, 0),new ennemi(4, 1,0),new ennemi(5, 1, 0), new ennemi(6, 1, 0), new ennemi(7, 1, 0),new ennemi(8, 1, 0),new ennemi(9, 1, 0), new ennemi(10, 1, 0), new ennemi(11, 1, 0),new ennemi(12, 1, 0),new ennemi(13, 1, 0), new ennemi(14, 1, 0)}
{

    ui->setupUi(this);
   for (int i=0; i<15; i++){
        scene->addItem(Ennemi[i]); //On ajoute tous les ennemis a la scene
    }
    ui->graphicsView->setScene(scene);
    scene ->setSceneRect(-300, -300, 600, 600); //Pour que la scene soit fixe

    startTimer(1000/33); //environ periode de 30 ms

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    static int nouvelle_direction = 1;
    static bool monstre_descend = false;
    static bool premiere_fois = true;
    static int cpt = 0;

    if (Ennemi[0]->pos().x() - 30 + (Ennemi[0]->getNumero()-7)*40 <= -700 && premiere_fois == true ){ //"(Ennemi[0]->getNumero()-7)*40" car il faut prendre en compte la position initiale, a la cretion du monstre, cf. ennemi.h : painter

        nouvelle_direction =  1;
        monstre_descend = true;

        cpt = 0; //reinitialisation du compteur
        premiere_fois = false;

    }
    else if(Ennemi[14]->pos().x() + 30 + (Ennemi[14]->getNumero()-7)*40 >= 600 && premiere_fois == true){
        nouvelle_direction =  - 1;
        monstre_descend = true;

        cpt = 0;
        premiere_fois = false;
    }

    if (cpt == 200){ //On utilise un compteur car le monstre se deplace lentement, toute les seconde, ainsi il ne sera pas bloque a descendre sans arret
        premiere_fois = true;
    }

    if(cpt == 34){ //environ 1 seconde (34 * 30 ms) car l'ennemi change de position toute les secondes
        monstre_descend = false; //On ne descend plus

    }


    for (int i=0; i<15; i++){
        Ennemi[i]->setDirection(nouvelle_direction);
        Ennemi[i]->setDescendre(monstre_descend);
    }

    cpt++;

}
