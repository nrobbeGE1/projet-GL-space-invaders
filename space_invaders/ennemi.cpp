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
bool ennemi::getPret_a_Tirer(){
    return m_pret_a_tirer;
}

void ennemi::setPret_a_Tirer(bool pret_a_tirer) {
    m_pret_a_tirer = pret_a_tirer;
}

int ennemi::getLigne(){
    return m_ligne;
}

void ennemi::setVitesse(int dx){
    m_dx = dx;
}

int ennemi::getVitesse(){
    return m_dx;
}

void ennemi::reinitialisation(void){
    setPos(0, 0);
    setEnabled(true);
    show();
}