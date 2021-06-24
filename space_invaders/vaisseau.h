#ifndef VAISSEAU_H
#define VAISSEAU_H

#define HAUTEUR_VAISSEAU 350

#include <QGraphicsObject>
#include <QPainter>
#include <QKeyEvent>
#include <QCursor>


class Vaisseau : public QGraphicsObject
{
public:
    Vaisseau() {        //constructeur du vaisseau
        startTimer(1000/33); //1000 ms = 1 s
        setPos(QPointF(m_pos_vaisseau));
    }

    virtual QRectF boundingRect() const override{       //hitbox
        QRectF rect(-25, -25, 50, 50);
        return rect;
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override       //ajout sprite (photo)
    {
        painter -> drawImage(QRectF(-25, -25, 50, 50), QImage(":/vaisseau.png"));
    }

    void bouge_gauche(void) {
        if (pos().x() > -375) setPos(QPointF(pos().x() - 10, pos().y()));       //deplacement vers la gauche + gestion bordure deplacement
    }
    void bouge_droite(void) {
        if (pos().x() < 375) setPos(QPointF(pos().x() + 10, pos().y()));        //deplacement vers la droite + gestion bordure deplacement
    }

    void timerEvent(QTimerEvent *event) override {
        static QPointF old_position_souris;
        QPointF new_position_souris = QCursor::pos();
        if (new_position_souris.x() < old_position_souris.x()) bouge_gauche();      //si la nouvelle valeur est plus faible -> deplacement a gauche
        else if (new_position_souris.x() > old_position_souris.x()) bouge_droite();     //si la nouvelle valeur est plus grande -> deplacement a droite
        old_position_souris = new_position_souris;      //on attribue la nouvelle valeur a la place de l'ancienne pour les prochains tests
    }

    double transfert_position_x_vaisseau() {
        return pos().x();       //assesseur pour recuperer la position du vaisseau
    }

private:
    QPointF m_pos_vaisseau = QPointF(0,HAUTEUR_VAISSEAU);
};

#endif // VAISSEAU_H
