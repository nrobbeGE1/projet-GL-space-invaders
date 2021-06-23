#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <QGraphicsObject>
#include <QPainter>
#include <QKeyEvent>
#include <QCursor>


class vaisseau : public QGraphicsObject
{
public:
    vaisseau() {        //constructeur du vaisseau
        startTimer(1000/33); //1000 ms = 1 s
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

    void bouge_gauche(void);
    void bouge_droite(void);

    void timerEvent(QTimerEvent *event) override {
        static QPointF position_souris;
        QPointF new_position_souris = QCursor::pos();
        if (new_position_souris.x() < position_souris.x()) bouge_gauche();
        else if (new_position_souris.x() > position_souris.x()) bouge_droite();
        position_souris = new_position_souris;
    }

private:
    QPointF m_pos_vaisseau = QPointF(0,300);
};

#endif // VAISSEAU_H