#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ennemi.cpp"
#include <QGraphicsSimpleTextItem>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene),m_text_item (new QGraphicsSimpleTextItem(QString("APPUYER SUR LA BARRE D'ESPACE POUR DEMARRER"))), Ennemi{new ennemi(0, 1, 0), new ennemi(1, 1, 0), new ennemi(2, 1, 0), new ennemi(3,1, 0),new ennemi(4, 1,0),new ennemi(5, 1, 0), new ennemi(6, 1, 0), new ennemi(7, 1, 0),new ennemi(8, 1, 0),new ennemi(9, 1, 0), new ennemi(10, 1, 0), new ennemi(11, 1, 0),new ennemi(12, 1, 0),new ennemi(13, 1, 0), new ennemi(14, 1, 0)}, Ennemi2{new ennemi(15, 1, 0), new ennemi(16, 1, 0), new ennemi(17, 1, 0), new ennemi(18,1, 0),new ennemi(19, 1,0),new ennemi(20, 1, 0), new ennemi(21, 1, 0), new ennemi(22, 1, 0),new ennemi(23, 1, 0),new ennemi(24, 1, 0), new ennemi(25, 1, 0), new ennemi(26, 1, 0),new ennemi(27, 1, 0),new ennemi(28, 1, 0), new ennemi(29, 1, 0)}, vaisseau_joueur(new Vaisseau), tir_joueur(new Projectile)
{

    ui->setupUi(this);

    m_text_item->setFont(QFont("OldEnglish", 20));//Police de caractere et taille de caractere
    m_text_item->setPen(QPen(Qt::white, 2));

    m_text_item->setPos(-350,100);



   for (int i=0; i<15; i++){
        scene->addItem(Ennemi[i]); //On ajoute tous les ennemis a la scene
        scene->addItem(Ennemi2[i]);
    }

    scene->addItem(m_text_item);

    ui->graphicsView->setScene(scene);
    scene ->setSceneRect(-300, -300, 600, 600); //Pour que la scene soit fixe


    scene->addItem(vaisseau_joueur);
    scene->addItem(tir_joueur);
    tir_joueur->hide();
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

    static int pos_init_ligne1_monstre0 = (0 - 7) *40; //(Ennemi[0]->getNumero() = 0 et "(0-7)*40" car il faut prendre en compte la position initiale, a la cretion du monstre, cf. ennemi.h : painter
    static int pos_init_ligne1_monstre14 = (14 - 7) *40;

    static int pos_init_ligne2_monstre0 = (15 - 22) *40;
    static int pos_init_ligne2_monstre14 = (29 - 22) *40;

    if ((Ennemi[0]->pos().x() - 30 + pos_init_ligne1_monstre0 <= -700 || Ennemi2[0]->pos().x() - 30 + pos_init_ligne2_monstre0 <= -700) && premiere_fois == true ){

        nouvelle_direction =  1;
        monstre_descend = true;

        cpt = 0; //reinitialisation du compteur
        premiere_fois = false;

    }
    else if((Ennemi[14]->pos().x() + 30 + pos_init_ligne1_monstre14 >= 600 || Ennemi2[14]->pos().x() + 30 + pos_init_ligne2_monstre14 >= 600) && premiere_fois == true){
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
        Ennemi[i]->setDirection(nouvelle_direction); //Premiere ligne de monstre
        Ennemi[i]->setDescendre(monstre_descend);

        Ennemi2[i]->setDirection(nouvelle_direction); //Seconde ligne de monstre
        Ennemi2[i]->setDescendre(monstre_descend);
    }

    cpt++;

    QList <QGraphicsItem*> items_dangereux = scene->collidingItems(tir_joueur);     //gestion des collisions entre le projectile et les ennemis
    for (QGraphicsItem * item: items_dangereux) {
        for (int i = 0; i <= 14; i ++) {        //pour tester les collisions avec tous les ennemis sans les déclarer un par un
            if (item == Ennemi[i]) {
                qDebug("Ennemi %d touche", i);
                tir_joueur->hide();
                Ennemi[i]->hide();
                score += 10;
                qDebug("Score = %d", score);
            }
            if (item == Ennemi2[i]) {
                qDebug("Ennemi2 %d touche", i);
                tir_joueur->hide();
                Ennemi2[i]->hide();
                score += 10;
                qDebug("Score = %d", score);
            }
        }
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()){
    case Qt::Key_Q:
            vaisseau_joueur->bouge_gauche();        //si appui sur Q -> deplacement gauche
            break;
        case Qt::Key_D:
            vaisseau_joueur->bouge_droite();        //si appui sur D -> deplacement droite
            break;
    case Qt::Key_Space:         //tir sur appui espace
        if (tir_joueur->projectile_move == false) {
                    tir_joueur->set_position_x(vaisseau_joueur->transfert_position_x_vaisseau());
                    tir_joueur->projectile_move = true;
                }
        startTimer(1000/33);

        for(int i=0; i<15; i++){
            Ennemi[i]->startTimer(1000);
            Ennemi2[i]->startTimer(1000);
        }

        m_text_item->setText("");
        break;
    }
}
