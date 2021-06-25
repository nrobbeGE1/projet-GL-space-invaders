#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ennemi.cpp"
#include <QGraphicsSimpleTextItem>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene), m_premiere_fois_start(true), m_timer_window(0), m_text_item (new QGraphicsSimpleTextItem(QString("APPUYER SUR LA BARRE D'ESPACE POUR DEMARRER"))), m_num_score(0), m_score(new QGraphicsSimpleTextItem(QString("Score : "+QString::number(m_num_score)))), m_num_vie(3), m_vie(new QGraphicsSimpleTextItem(QString("PV : "+QString::number(m_num_vie)))), vaisseau_joueur(new Vaisseau)
{
    for(int i=0; i<15; i++){
        Ennemi[i] = new ennemi(i,0,1);
        Ennemi2[i] = new ennemi(i+15,0,1);
    }

    for (int i=0; i<5; i++) {
        tir_joueur[i] = new Projectile(false);  //false --> type de projectile: joueur (projectile montant)
    }
    for (int i=0; i<5; i++) {
        tir_ennemi[i] = new Projectile(true);  //true --> type de projectile: ennemi (projectile descendant)
    }

    ui->setupUi(this);

    m_text_item->setFont(QFont("OldEnglish", 20));//Police de caractere et taille de caractere
    m_text_item->setPen(QPen(Qt::white, 2));

    m_score->setFont(QFont("OldEnglish", 20));//Police de caractere et taille de caractere
    m_score->setPen(QPen(Qt::white, 2));

    m_vie->setFont(QFont("OldEnglish", 20));//Police de caractere et taille de caractere
    m_vie->setPen(QPen(Qt::white, 2));

    m_text_item->setPos(-350,100);
    m_score->setPos(400, -350);
    m_vie->setPos(-400, -350);



    for (int i=0; i<15; i++){
        scene->addItem(Ennemi[i]); //On ajoute tous les ennemis a la scene
        scene->addItem(Ennemi2[i]);
    }

    scene->addItem(m_text_item);
    scene->addItem(m_score);
    scene->addItem(m_vie);

    ui->graphicsView->setScene(scene);
    scene ->setSceneRect(-300, -300, 600, 600); //Pour que la scene soit fixe

    scene->addItem(vaisseau_joueur);

    for (int i=0; i<5; i++) {
        scene->addItem(tir_joueur[i]);      //on ajoute les 5 projectiles a la scene...
        tir_joueur[i]->hide();         //puis on les cache
        tir_joueur[i]->setEnabled(false);
    }
    for (int i=0; i<5; i++) {
        scene->addItem(tir_ennemi[i]);      //on ajoute les 5 projectiles a la scene...
        tir_ennemi[i]->hide();         //puis on les cache
        tir_ennemi[i]->setEnabled(false);
    }

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


    if(m_num_vie == 0 && m_premiere_fois_start == false){ //Fin du jeu

        killTimer(m_timer_window);
        m_text_item->setText("| GAME OVER | APPUYER SUR LA BARRE D'ESPACE POUR DEMARRER");
        for(int i=0; i<15; i++){
            qDebug("ok");
            Ennemi[i]->killTimer(m_id_timer_monstre[i]);
            Ennemi2[i]->killTimer(m_id_timer_monstre[i + 15]);
        }
        m_premiere_fois_start = true;
    }

    cpt++;

    for(int j=0; j<5; j++) {
        QList <QGraphicsItem*> items_dangereux = scene->collidingItems(tir_joueur[j]);     //gestion des collisions entre le projectile et les ennemis
        for (QGraphicsItem * item: items_dangereux) {
            for (int i = 0; i <= 14; i ++) {        //pour tester les collisions avec tous les ennemis sans les déclarer un par un
                if (item == Ennemi[i]) {
                    if(tir_joueur[j]->isEnabled()){
                        m_num_score += 10;
                        m_score->setText("Score : "+QString::number(m_num_score));
                        tir_joueur[j]->hide();
                        tir_joueur[j]->setEnabled(false);
                        Ennemi[i]->hide();
                        Ennemi[i]->setEnabled(false);
                    }
                }
                if (item == Ennemi2[i]) {
                    if(tir_joueur[j]->isEnabled()){
                        m_num_score += 10;
                        m_score->setText("Score : "+QString::number(m_num_score));
                        Ennemi2[i]->hide();
                        Ennemi2[i]->setEnabled(false);
                        tir_joueur[j]->hide();
                        tir_joueur[j]->setEnabled(false);
                    }
                }
            }
        }
    }


    for (int i=0; i<15; i++) {
        if (Ennemi[i]->getPret_a_Tirer() and isEnabled()) {
            qDebug("creation projectile 1 %d %d ",(Ennemi[i]->getPret_a_Tirer() && isEnabled()), i);
            tir_ennemi[sel_projectile_ennemi]->set_position_x(Ennemi[i]->pos().x());
            tir_ennemi[sel_projectile_ennemi]->set_position_y(Ennemi[i]->pos().y());
            tir_ennemi[sel_projectile_ennemi]->projectile_move = true;
            tir_ennemi[sel_projectile_ennemi]->setEnabled(true);
            Ennemi[i]->setPret_a_Tirer(false);
            qDebug("fin 1");
            if (sel_projectile_ennemi == 4) sel_projectile_ennemi = 0;
            else sel_projectile_ennemi ++;
        }
    }
    for (int i=0; i<15; i++) {
        if (Ennemi2[i]->getPret_a_Tirer() and isEnabled()) {
            qDebug("creation projectile 2 %d %d",(Ennemi2[i]->getPret_a_Tirer() && isEnabled()), i);
            tir_ennemi[sel_projectile_ennemi]->set_position_x(Ennemi2[i]->pos().x());
            tir_ennemi[sel_projectile_ennemi]->set_position_y(Ennemi2[i]->pos().y());
            tir_ennemi[sel_projectile_ennemi]->projectile_move = true;
            tir_ennemi[sel_projectile_ennemi]->setEnabled(true);
            Ennemi2[i]->setPret_a_Tirer(false);
            qDebug("fin 2");
            if (sel_projectile_ennemi == 4) sel_projectile_ennemi = 0;
            else sel_projectile_ennemi ++;
        }
    }


    QList <QGraphicsItem*> ennemis_dangereux = scene->collidingItems(vaisseau_joueur);
    for (QGraphicsItem * item: ennemis_dangereux) {
        for (int i = 0; i <= 14; i ++) {        //pour tester les collisions avec tous les ennemis sans les déclarer un par un
            if (item == Ennemi[i]) {
                vaisseau_joueur->hide();
                m_num_vie = 0;
            }
            if (item == Ennemi2[i]) {
                vaisseau_joueur->hide();
                m_num_vie = 0;
            }
        }
    }



}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()){
    case Qt::Key_Q:
        if (!m_premiere_fois_start) vaisseau_joueur->bouge_gauche();        //si appui sur Q -> deplacement gauche
        break;
    case Qt::Key_D:
        if (!m_premiere_fois_start) vaisseau_joueur->bouge_droite();        //si appui sur D -> deplacement droite
        break;
    case Qt::Key_Space:         //tir sur appui espace
        vaisseau_joueur->startTimer(1000/33); //1000 ms = 1 s
        if(m_premiere_fois_start){
            m_timer_window = startTimer(1000/33);
            m_premiere_fois_start = false;

            for(int i=0; i<15; i++){
                m_id_timer_monstre[i] = Ennemi[i]->startTimer(1000);
                m_id_timer_monstre[i+15] = Ennemi2[i]->startTimer(1000);
            }
            m_text_item->setText("");
            m_num_vie = 3;
            m_num_score = 0;
            m_score->setText("Score : "+QString::number(m_num_score));
            m_premiere_fois_start = false;
        }
        else {       //on incremente la variable <sel_projectile> a chaque tir, c'est elle qui indique quel projectile est tire
            if (tir_joueur[sel_projectile_vaisseau]->projectile_move == false) {
                tir_joueur[sel_projectile_vaisseau]->set_position_x(vaisseau_joueur->transfert_position_x_vaisseau());
                tir_joueur[sel_projectile_vaisseau]->projectile_move = true;
                tir_joueur[sel_projectile_vaisseau]->setEnabled(true);
                if (sel_projectile_vaisseau == 4) sel_projectile_vaisseau = 0;
                else sel_projectile_vaisseau ++;
            }
        }
        break;
    }
}
