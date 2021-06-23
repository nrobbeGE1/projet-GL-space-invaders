#ifndef ENNEMI_H
#define ENNEMI_H

#include <QGraphicsObject>
#include <QPainter>

class ennemi : public QGraphicsObject
{
private:

    int m_numero;
    int m_direction;
    bool m_descendre;
    QPointF m_pos;
    int m_cpt_animation;

public:
    ennemi(int numero = 0, int direction = 1, int descendre = 0, QPointF position = QPointF(0,0), int cpt_animation = 0): m_numero(numero), m_direction(direction), m_descendre(descendre), m_pos(position), m_cpt_animation(cpt_animation) {

    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
    {
        static int deuxieme_ligne, espacement;

        if(m_numero > 14){ // 15<= m_numero <= 29

            deuxieme_ligne = 25; //Si le numero du monstre > 14 c'est un monstre de la deuxieme ligne, on le place un peu plus en bas
            espacement = 40*(m_numero - 22); //gere l'espacement entre les monstre
        }

        else{ // 0 <= m_numero <= 14

            deuxieme_ligne = 0;
            espacement = 40*(m_numero - 7);
        }

        if(m_cpt_animation%2 ==0) painter -> drawImage(QRectF(espacement, deuxieme_ligne, 30, 30), QImage(":/monstre_up.png")); //On dessine les monstres sur une meme ligne, espaces les uns des autres
        else painter -> drawImage(QRectF(espacement, deuxieme_ligne, 30, 30), QImage(":/monstre_down.png"));



    }

    virtual QRectF boundingRect() const override{
        static int deuxieme_ligne, espacement;

        if(m_numero > 14){ // 15<= m_numero <= 29
            deuxieme_ligne = 25;
            espacement = 40*(m_numero - 22); //gere l'espacement entre les monstre
        }

        else{ // 0 <= m_numero <= 14
            deuxieme_ligne = 0;
            espacement = 40*(m_numero - 7);
        }

        QRectF rect(espacement, deuxieme_ligne, 30, 30);

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


        m_pos = QPointF(m_dx, m_dy);

    }

    int getDirection();
    void setDirection(int direction);
    void setDescendre(bool descendre);


};
#endif // ENNEMI_H
