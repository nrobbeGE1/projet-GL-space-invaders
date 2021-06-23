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
        QRectF rect(m_position_tir_X, 280, 4, 10);
        return rect;
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override       //ajout sprite (photo)
    {
        if (projectile_move) painter -> drawImage(QRectF(m_position_tir_X, 280, 4, 10), QImage(":/tir_joueur.png"));
    }

    void timerEvent(QTimerEvent *event) override {
        if (projectile_move && m_position_tir_joueur.y() > -299) {
            show();
            m_position_tir_joueur = QPointF(pos().x(), pos().y() - 20);
            setPos(m_position_tir_joueur);
        }
        else if (m_position_tir_joueur.y() <= -299) {
            m_position_tir_joueur = QPointF(pos().x(), 280);
            hide();
            projectile_move = false;
        }
    }

    void set_position_x(double position_x) {
        qDebug("%lf", position_x);
        m_position_tir_X = position_x;
    }

private:
    QPointF m_position_tir_joueur;
    double m_position_tir_X;
};

#endif // PROJECTILE_H
