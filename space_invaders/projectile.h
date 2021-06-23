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
    }

    virtual QRectF boundingRect() const override{       //bordure du projectile
        QRectF rect((m_position_tir_X - 2), (HAUTEUR_VAISSEAU - 30), 4, 10);
        return rect;
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override       //ajout sprite (photo)
    {
        painter -> drawImage(QRectF((m_position_tir_X - 2), (HAUTEUR_VAISSEAU - 30), 4, 10), QImage(":/tir_joueur.png"));
    }

    void timerEvent(QTimerEvent *event) override {
        if (projectile_move && m_position_tir_Y > -300) {
            show();
            m_position_tir_joueur = QPointF(pos().x(), m_position_tir_Y);
            setPos(m_position_tir_joueur);
            m_position_tir_Y -= 20;
        }
        else if (m_position_tir_Y <= -300) {
            projectile_move = false;
            hide();
        }
    }

    void set_position_x(double position_x_vaisseau) {
        m_position_tir_X = position_x_vaisseau;
        m_position_tir_Y = 0;
    }

private:
    QPointF m_position_tir_joueur;
    double m_position_tir_X;
    double m_position_tir_Y = 0;
};

#endif // PROJECTILE_H
