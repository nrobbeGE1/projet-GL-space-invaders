#include "vaisseau.h"

void vaisseau::bouge_gauche(void){
    if (pos().x() > -275) setPos(QPointF(pos().x() - 10, pos().y()));
}

void vaisseau::bouge_droite(void){
    if (pos().x() < 275) setPos(QPointF(pos().x() + 10, pos().y()));
}
