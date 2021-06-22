#ifndef ENNEMI_H
#define ENNEMI_H

#include <QGraphicsObject>
#include <QPainter>

class ennemi : public QGraphicsObject
{
private:

    int m_numero;
    QPointF m_pos;

public:
    ennemi(int numero = 1, QPointF position = QPointF(0,0)): m_numero(numero), m_pos(position){
        startTimer(1000/33); //1000 ms = 1 s
       setPos(QPointF(m_pos));
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
    {

        painter -> drawImage(QRectF(-300 + 35*m_numero,0, 30, 30), QImage(":/monstre_down.png"));

    }

    virtual QRectF boundingRect() const override{

        QRectF rect(0, 0, 30, 30);
        return rect;
    }

};
#endif // ENNEMI_H
