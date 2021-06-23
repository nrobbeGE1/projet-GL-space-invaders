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

public:
    ennemi(int numero = 0, int direction = 1, int descendre = 0, QPointF position = QPointF(0,0)): m_numero(numero), m_direction(direction), m_descendre(descendre), m_pos(position) {
        startTimer(1000); //1000 ms = 1 s
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
    {

        painter -> drawImage(QRectF((m_numero-7)*40,0, 30, 30), QImage(":/monstre_down.png")); //On dessine les monstres sur une meme ligne, espaces les uns des autres

    }

    virtual QRectF boundingRect() const override{

        QRectF rect(40*(m_numero-7), 0, 30, 30);
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

        m_pos = QPointF(m_dx, m_dy);

    }

    int getDirection();
    int getNumero();
    void setDirection(int direction);
    void setDescendre(bool descendre);


};
#endif // ENNEMI_H
