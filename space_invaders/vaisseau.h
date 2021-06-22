#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <QGraphicsObject>
#include <QPainter>
#include <QKeyEvent>

class vaisseau : public QGraphicsObject
{
public:
    vaisseau() {        //constructeur du vaisseau
        //startTimer(1000/33); //1000 ms = 1 s
        setPos(QPointF(m_pos_vaisseau));
    }

    virtual QRectF boundingRect() const override{       //bordure
            QRectF rect(-25, -25, 50, 50);
            return rect;
        }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override       //ajout sprite (photo)
        {
            painter -> drawImage(QRectF(-25, -25, 50, 50), QImage(":/vaisseau.png"));
        }



private:
    QPointF m_pos_vaisseau = QPointF(0,300);
};

#endif // VAISSEAU_H
