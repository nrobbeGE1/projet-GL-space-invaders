#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <QGraphicsObject>
#include <QPainter>

class vaisseau : public QGraphicsObject
{
public:
    vaisseau() {        //constructeur du vaisseau
        startTimer(1000/33); //1000 ms = 1 s
        setPos(QPointF(m_pos_vaisseau));
    }

    virtual QRectF boundingRect() const override{       //bordure
            QRectF rect(0, 0, 50, 50);
            return rect;
        }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override       //ajout sprite (photo)
        {
            painter -> drawImage(QRectF(0,0, 50, 50), QImage(":/vaisseau.png"));
        }

    void timerEvent(QTimerEvent *event) override {      //gestion deplacement
        QPointF position_actuelle_vaisseau = pos();

        setPos(m_pos_vaisseau + position_actuelle_vaisseau);
        if (true) m_pos_vaisseau = QPointF(-5, 0);
        else if (true) m_pos_vaisseau = QPointF(5, 0);
    }

private:
    int m_vie;
    QPointF m_pos_vaisseau = QPointF(0,0);
};

#endif // VAISSEAU_H
