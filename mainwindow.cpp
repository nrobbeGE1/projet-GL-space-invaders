#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ennemi.cpp"
#include <QGraphicsSimpleTextItem>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene), m_premiere_fois_start(true), m_timer_window(0), m_text_item (new QGraphicsSimpleTextItem(QString("APPUYER SUR LA BARRE D'ESPACE POUR DEMARRER"))), m_num_score(0), m_score(new QGraphicsSimpleTextItem(QString("Score : "+QString::number(m_num_score)))), m_num_vie(3), m_vie(new QGraphicsSimpleTextItem(QString("PV : "+QString::number(m_num_vie)))), vaisseau_joueur(new Vaisseau)
{

    QPixmap image_fond (":/ciel.jpg");
    scene->setBackgroundBrush(image_fond);

    val_timer = 1000;
    for(int i= 0; i<5; i++){
        elimine_ligne[i] = 0;
    }

    for(int i=0; i<5; i++){
        for(int j=0 ; j<15; j++){

            if(i == 4) Ennemi[j][i] = new ennemi(j +60,1,0, i);
            else if(i == 3) Ennemi[j][i] = new ennemi(j + 45,1,0, i);
            else if(i == 2) Ennemi[j][i] = new ennemi(j +30,1,0, i);
            else if(i == 1) Ennemi[j][i] = new ennemi(j+15, 1,0,i );
            else Ennemi[j][i] = new ennemi(j,1,0);
        }
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



    for(int i=0; i<5; i++){
        for(int j=0 ; j<15; j++){
            scene->addItem(Ennemi[j][i]);
        }
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

    if ((Ennemi[0][0]->pos().x() - 30 + pos_init_ligne1_monstre0 <= -500 || Ennemi[0][1]->pos().x() - 30 + pos_init_ligne2_monstre0 <= -500) && premiere_fois == true ){

        nouvelle_direction =  1;
        monstre_descend = true;

        cpt = 0; //reinitialisation du compteur
        premiere_fois = false;

    }
    else if((Ennemi[14][0]->pos().x() + 30 + pos_init_ligne1_monstre14 >= 500 || Ennemi[14][1]->pos().x() + 30 + pos_init_ligne2_monstre14 >= 500) && premiere_fois == true){
        nouvelle_direction =  - 1;
        monstre_descend = true;

        cpt = 0;
        premiere_fois = false;
    }

    if (cpt >= (225 - 100/val_timer)){ //On utilise un compteur car le monstre se deplace lentement, toute les seconde, ainsi il ne sera pas bloque a descendre sans arret
        premiere_fois = true;
    }

    if(cpt >= 34 - 60/val_timer){ //environ 1 seconde (34 * 30 ms) car l'ennemi change de position toute les secondes
        monstre_descend = false; //On ne descend plus

    }

    cpt++;


    for(int i=0; i<5; i++){
        for (int j=0; j<15; j++){
            Ennemi[j][i]->setDirection(nouvelle_direction);
            Ennemi[j][i]->setDescendre(monstre_descend);
        }
    }


    if(m_num_vie == 0 && m_premiere_fois_start == false){ //Fin du jeu

        killTimer(m_timer_window);
        m_text_item->setText("| GAME OVER | APPUYER SUR LA BARRE D'ESPACE POUR DEMARRER");
        for(int i=0; i<5; i++){
            for(int j=0; j<15; j++){
                Ennemi[j][i]->killTimer(m_id_timer_monstre[j][i]);
            }
        }
        m_premiere_fois_start = true;
    }

    for(int s=0; s <5; s++){ //gestion acceleration des ennemis quand les lignes meurts

        if(elimine_ligne[s] == 15){
            val_timer-= 100;
            elimine_ligne[s] = 0;
            for(int v = 0; v<15; v++){
                for(int b= 0; b <5; b++){
                    killTimer(m_id_timer_monstre[v][b]);
                    m_id_timer_monstre[v][b] = Ennemi[v][b]->startTimer(val_timer);
                }
            }
        }
    }





    for(int g=0; g<5; g++) {
        QList <QGraphicsItem*> items_dangereux = scene->collidingItems(tir_joueur[g]);     //gestion des collisions entre le projectile et les ennemis
        for (QGraphicsItem * item: items_dangereux) {
            for(int i=0; i<5; i++){
                for (int j = 0; j < 15; j ++) {        //pour tester les collisions avec tous les ennemis sans les déclarer un par un

                    if (item == Ennemi[j][i]) {
                        if(tir_joueur[g]->isEnabled()){

                            if(i == 0) m_num_score += 30;
                            else if(i == 1 || i == 2) m_num_score += 20;
                            else if(i == 3 || i == 4) m_num_score += 10;

                            elimine_ligne[i] +=1; //¨pour gerer l'acceleration des ennemis

                            m_score->setText("Score : "+QString::number(m_num_score));
                            tir_joueur[g]->hide();
                            tir_joueur[g]->setEnabled(false);
                            Ennemi[j][i]->hide();
                            Ennemi[j][i]->setEnabled(false);
                        }
                    }
                }
            }
        }
        QList <QGraphicsItem*> ennemi_dangereux = scene->collidingItems(tir_ennemi[g]);     //gestion des collisions entre le projectile et les ennemis
        for (QGraphicsItem * item: ennemi_dangereux) {//pour tester les collisions avec tous les ennemis sans les déclarer un par un
            if (item == vaisseau_joueur) {
                if(tir_ennemi[g]->isEnabled()){
                    m_num_vie -= 1;
                    m_vie->setText("PV : "+QString::number(m_num_vie));
                    tir_ennemi[g]->hide();
                    tir_ennemi[g]->setEnabled(false);
                }
            }
        }

        QList <QGraphicsItem*> tir_dangereux = scene->collidingItems(tir_joueur[g]);
        for (QGraphicsItem * item: tir_dangereux) {
            if (item == tir_ennemi[g]) {
                if (tir_joueur[g]->isEnabled() and tir_ennemi[g]->isEnabled()) {
                    tir_joueur[g]->hide();
                    tir_joueur[g]->setEnabled(false);
                    tir_ennemi[g]->hide();
                    tir_ennemi[g]->setEnabled(false);
                }
            }
        }
    }


    for (int j=0; j<5; j++) {
        for (int i=0; i<15; i++) {
            if (Ennemi[i][j]->getPret_a_Tirer() and isEnabled()) {
                tir_ennemi[sel_projectile_ennemi]->set_position_x(Ennemi[i][j]->transfert_position_x_ennemi((i-7)*40));
                tir_ennemi[sel_projectile_ennemi]->set_position_y(Ennemi[i][j]->transfert_position_y_ennemi(j));
                tir_ennemi[sel_projectile_ennemi]->projectile_move = true;
                tir_ennemi[sel_projectile_ennemi]->setEnabled(true);
                Ennemi[i][j]->setPret_a_Tirer(false);
                if (sel_projectile_ennemi == 4) sel_projectile_ennemi = 0;
                else sel_projectile_ennemi ++;
            }
        }
    }


    QList <QGraphicsItem*> ennemis_dangereux = scene->collidingItems(vaisseau_joueur);
    for (QGraphicsItem * item: ennemis_dangereux) {
        for(int i=0; i<5; i++){
            for (int j = 0; j < 15; j ++) {        //pour tester les collisions avec tous les ennemis sans les déclarer un par un
                if (item == Ennemi[j][i]) {
                    vaisseau_joueur->hide();
                    m_num_vie = 0;
                }
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
        if(m_premiere_fois_start){ // Si le jeu demarre pour la premiere fois, initialisation du jeu
            m_timer_window = startTimer(1000/33);
            vaisseau_joueur->startTimer(1000/33); //1000 ms = 1 s

            for(int i=0; i<5; i++){
                for(int j=0; j<15; j++){
                    if(i == 1) m_id_timer_monstre[j][i] = Ennemi[j][i]->startTimer(1000);
                    else m_id_timer_monstre[j][i] = Ennemi[j][i]->startTimer(1000);
                }
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
