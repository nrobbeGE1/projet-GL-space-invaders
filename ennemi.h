#ifndef ENNEMI_H
#define ENNEMI_H

#include <QGraphicsObject>
#include <QPainter>
#include <time.h>
#include <cstdlib>

class ennemi : public QGraphicsObject
{
private:

    int m_numero;
    int m_direction;
    bool m_descendre;
    int m_ligne; // pour connaitre la ligne du monstre (poulpe, meduse, monstre rouge...)
    QPointF m_pos;
    int m_cpt_animation;
    bool m_pret_a_tirer;

public:
    ennemi(int numero = 0, int direction = 1, int descendre = 0, int ligne = 0, QPointF position = QPointF(0,0), int cpt_animation = 0, bool pret_a_tirer = false): m_numero(numero), m_direction(direction), m_descendre(descendre),m_ligne(ligne), m_pos(position), m_cpt_animation(cpt_animation) {
        srand(time(0));
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
    {
        static int lignes[5] = {-230, -190, -160,-130, -95}, espacement[5];
        //Plus la ligne du monstre est petite, plus on le place un peu plus en haut

        espacement[m_ligne] = 60*(m_numero - (7 + (15*m_ligne))); //gere l'espacement entre les monstres

        switch(m_ligne){
        case 0:
            if(m_cpt_animation%2 ==0) painter -> drawImage(QRectF(espacement[0], lignes[0], 30, 30), QImage(":/poulpe2.png")); //On dessine les monstres sur une meme ligne, espaces les uns des autres
            else painter -> drawImage(QRectF(espacement[0], lignes[0], 30, 30), QImage(":/poulpe.png"));
            break;

        case 1 :
            if(m_cpt_animation%2 ==0) painter -> drawImage(QRectF(espacement[1], lignes[1], 30, 30), QImage(":/monstre_up.png")); //On dessine les monstres sur une meme ligne, espaces les uns des autres
            else painter -> drawImage(QRectF(espacement[1], lignes[1], 30, 30), QImage(":/monstre_down.png"));
            break;

        case 2:
            if(m_cpt_animation%2 ==0) painter -> drawImage(QRectF(espacement[2], lignes[2], 30, 30), QImage(":/monstre_up.png")); //On dessine les monstres sur une meme ligne, espaces les uns des autres
            else painter -> drawImage(QRectF(espacement[2], lignes[2], 30, 30), QImage(":/monstre_down.png"));
            break;

        case 3 :
            if(m_cpt_animation%2 ==0) painter -> drawImage(QRectF(espacement[3], lignes[3], 30, 30), QImage(":/meduse2.png")); //On dessine les monstres sur une meme ligne, espaces les uns des autres
            else painter -> drawImage(QRectF(espacement[3], lignes[3], 30, 30), QImage(":/meduse.png"));
            break;

        case 4:
            if(m_cpt_animation%2 ==0) painter -> drawImage(QRectF(espacement[4], lignes[4], 30, 30), QImage(":/meduse2.png")); //On dessine les monstres sur une meme ligne, espaces les uns des autres
            else painter -> drawImage(QRectF(espacement[4], lignes[4], 30, 30), QImage(":/meduse.png"));
            break;
        }
    }




    virtual QRectF boundingRect() const override{
        static int lignes[5] =  {-230, -190, -160,-130, -95}, espacement[5];
        //Plus la ligne du monstre est petite, plus on le place un peu plus en haut

        espacement[m_ligne] = 60*(m_numero - (7 + (15*m_ligne))); //gere l'espacement entre les monstres

        QRectF rect(espacement[m_ligne], lignes[m_ligne], 30, 30);

        return rect;
    }


    void timerEvent(QTimerEvent *event) override{
        static int m_dx;
        static int m_dy;

        QPointF position_actuelle = pos();
        setPos(position_actuelle + m_pos);

        if(m_direction == 1){
            m_dx = 15; //Si m_descendre vaut 1, le monstre descend, sinon il reste sur sa ligne
        }
        else if (m_direction == -1){
            m_dx = -15;
        }

        if(m_descendre == true) {

            m_dy = 15;
            m_dx = 0; //Quand le monstre descend il ne se deplace à gauche ou à droite
        }
        else{
            m_dy = 0;
        }

        if(m_cpt_animation == 60) m_cpt_animation = 0;
        else m_cpt_animation++;

        if(m_pret_a_tirer) m_pret_a_tirer = false;
        else{
            if((rand()%10 +1) == 7) m_pret_a_tirer = true;
        }

        m_pos = QPointF(m_dx, m_dy);

    }

    int getDirection();
    void setDirection(int direction);
    void setDescendre(bool descendre);
    bool getPret_a_Tirer();
    int getLigne();

};
#endif // ENNEMI_H
