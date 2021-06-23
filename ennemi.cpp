#include "ennemi.h"

int ennemi::getDirection(){
    return m_direction;
}

void ennemi::setDirection(int direction){
    m_direction = direction;
}

void ennemi::setDescendre(bool descendre){
    m_descendre = descendre;
}
