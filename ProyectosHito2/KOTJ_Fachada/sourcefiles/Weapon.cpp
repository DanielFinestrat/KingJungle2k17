/* 
 * File:   weapon.cpp
 * Author: pedro
 * 
 * Created on 16 de marzo de 2017, 20:24
 */

#include "../headerfiles/Weapon.h"
#include "../headerfiles/Partida.h"

Weapon::Weapon(sf::Vector2f size, sf::Vector2f pos, float shoot_cad, int Bps, int amm, int recoil_, bool parabola, bool explosivo) {

    tag = "Weapon";

    shootCadence = shoot_cad;
    BPS = Bps;
    m_Size = size;
    ammo = amm;
    recoil = recoil_;

    this->parabola = parabola;
    this->explosivo = explosivo;
    
    inPossession = false;
    dir = 1;
    difTime = (1 / shootCadence) * 1000;
    
    cuerpo = Motorfisico::getInstance()->crearCuerpo(0, 0, size.x, size.y);
    cuerpo->setPosicion(pos.x * MPP, pos.y * MPP);
    cuerpo->setMaskBits(MASK_GUN);
    cuerpo->setCategoryBits(CATEGORY_GUN);
    cuerpo->setDensity(1.0f);
    cuerpo->setFriction(0.2f);
    cuerpo->setRestitution(0.2f);
    cuerpo->setGravityScale(1.0f);
    
    //Creacion del cuerpo visible (shape)
    m_vBody = new VisibleBody(pos.x * PPM, pos.y * PPM, size.x, size.y, "./resources/sprites/revolver.png");

}

void Weapon::update() {
    m_vBody->updateBody(cuerpo->getPosicionX() * PPM, cuerpo->getPosicionY() * PPM, cuerpo->getAngulo()*180);
}

void Weapon::update(float posX, float posY) {
    cuerpo->setPosicion(posX, posY);
    m_vBody->updateBody(posX * PPM, posY * PPM, cuerpo->getAngulo()*180);
}

int Weapon::shoot() {
    if (ammo > 0) {
        dt = deltaClock.restart();
        difTime += dt.asSeconds();

        if (difTime >= shootCadence) {
            difTime = 0.0;
            ammo--;
            Partida *partida = Partida::getInstance();
            // +50 habria que cambiarlo por el size del personaje
            Bala* nuevaBala = new Bala(Vector2f(10, 4), Vector2f(cuerpo->getPosicionX() * PPM + 50 * dir, cuerpo->getPosicionY() * PPM), explosivo);
            
            if(!parabola) nuevaBala->Disparar(5 * -dir, 180);
            else nuevaBala->Disparar_Parabola(-dir, 160);
                
            partida->worldBullets.insert(nuevaBala);
            return recoil;
        }
    }
    return 0;
}

void Weapon::render(sf::RenderWindow *window) {
    window->draw(m_vBody->getShape());
}

void Weapon::setPossession(bool var) {
    inPossession = var;
}

void Weapon::throwWeapon(float playerVel) {

    inPossession = false;
    cuerpo->setActive(true);

    //Lanzarla para arriba si está quieto o anda despacio
    if (fabs(playerVel) < 0.3) cuerpo->aplicarFuerza(0, -80);
        //Lanzarla hacia donde mire la pistola
    else cuerpo->aplicarFuerza(dir * 70 * fabs(playerVel), -60);

}

void Weapon::setDir(int i) {
    dir = i;
    m_vBody->setScale(i, 1);
}

Weapon::~Weapon() {
}




