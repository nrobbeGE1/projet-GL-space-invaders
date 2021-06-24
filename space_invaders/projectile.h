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


    Projectile(bool type) {
        startTimer(1000/33); //1000 ms = 1 s
        m_type = type;
    }

    virtual QRectF boundingRect() const override{       //bordure du projectile
        if (!m_type) {
            QRectF rect((m_position_tir_X - 2), (HAUTEUR_VAISSEAU - 30), 4, 10);
            return rect;
        }
        else if (m_type) {
            QRectF rect((m_position_tir_X - 2), (m_position_tir_Y - 30), 4, 10);
            return rect;
        }
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override       //ajout sprite (photo)
    {
        if (!m_type) painter -> drawImage(QRectF((m_position_tir_X - 2), (HAUTEUR_VAISSEAU - 30), 4, 10), QImage(":/tir_joueur.png"));
        if (m_type) painter -> drawImage(QRectF((m_position_tir_X - 2), (m_position_tir_Y), 4, 10), QImage(":/tir_ennemi.png"));
    }

    void timerEvent(QTimerEvent *event) override {
        if (!m_type && projectile_move && m_position_tir_Y > -400) {       //le projectile se déplace jusqu'a atteindre cette borne
            m_position_tir_joueur = QPointF(pos().x(), m_position_tir_Y);
            setPos(m_position_tir_joueur);
            m_position_tir_Y -= 20;
        }
        else if (!m_type && m_position_tir_Y <= -400) {        //le projectile disparait et s'arrete
            projectile_move = false;
            hide();
        }
        if (m_type && projectile_move && m_position_tir_X < HAUTEUR_VAISSEAU) {
            m_position_tir_ennemi = QPointF(pos().x(), m_position_tir_Y);
            setPos(m_position_tir_ennemi);
            m_position_tir_Y += 5;
        }
        else if (m_type && m_position_tir_Y >= HAUTEUR_VAISSEAU) {
            projectile_move = false;
            hide();
        }
    }

    void set_position_x(double position_x_vaisseau_ou_ennemi) {       //recuperation position X (horizontale) vaisseau/ennemi
        m_position_tir_X = position_x_vaisseau_ou_ennemi;     //definition de l'origine du projectile
        m_position_tir_Y = 0;       //on en profite pour reset la hauteur du projectile a chaque tir
        show();
    }

    void set_position_y(double hauteur_ennemi) {
        m_position_tir_Y = hauteur_ennemi;
        show();
    }

private:
    QPointF m_position_tir_joueur;
    QPointF m_position_tir_ennemi;
    double m_position_tir_X;
    double m_position_tir_Y;
    bool m_type;    //type de projectile (false = joueur/true = ennemi)
};

#endif // PROJECTILE_H
