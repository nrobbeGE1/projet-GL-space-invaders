#include "vaisseau.h"

void vaisseau::bouge_gauche(void){
    setPos(QPointF(pos().x() - 5, pos().y()));
}

void vaisseau::bouge_droite(void){
    setPos(QPointF(pos().x() + 5, pos().y()));
}
