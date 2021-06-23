#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsObject>
#include <QPainter>
#include <QKeyEvent>
#include "vaisseau.h"

class Projectile : public QGraphicsObject
{
public:
    bool projectile_move = false;
    Projectile() {
        startTimer(1000/33); //1000 ms = 1 s
        setPos(QPointF(m_position_tir_joueur));
    }

    virtual QRectF boundingRect() const override{       //bordure du projectile
        QRectF rect(-2, -5, 4, 10);
        return rect;
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override       //ajout sprite (photo)
    {
        painter -> drawImage(QRectF(-2, -5, 4, 10), QImage(":/tir_joueur.png"));
    }

    void timerEvent(QTimerEvent *event) override {
        if (projectile_move) {
            show();
            m_position_tir_joueur = QPointF(pos().x(), pos().y() - 20);
            setPos(m_position_tir_joueur);
        }
    }

    void set_position(QPointF position) {
        m_position_tir_joueur = position;
    }

private:
    QPointF m_position_tir_joueur;

};

#endif // PROJECTILE_H
