
/* 
 * File:   weapon.cpp
 * Author: pedro
 * 
 * Created on 16 de marzo de 2017, 20:24
 */

#include "../headerfiles/Weapon.h"
#include "../headerfiles/Partida.h"
#include "../motorgrafico/headerfiles/Motorgrafico.h"

Weapon::Weapon(float sizex, float sizey, float posx, float posy, float shoot_cad, int Bps, int amm, int recoil_, int rango, bool parabola, bool explosivo) {

    tag = "Weapon";

    shootCadence = shoot_cad;
    BPS = Bps;
    m_sizex = sizex;
    m_sizey = sizey;
    ammo = amm;
    recoil = recoil_;
    this->rango = rango;
    
    if(rango == -1) balasVisibles = false;
    else balasVisibles = true;

    this->parabola = parabola;
    this->explosivo = explosivo;

    inPossession = false;
    used = false;
    dir = 1;
    difTime = (1 / shootCadence) * 1000;

    cuerpo = Motorfisico::getInstance()->crearCuerpo(0, 0, sizex, sizey, this);
    cuerpo->setPosicion(posx * MPP, posy * MPP);
    cuerpo->setMaskBits(MASK_GUN);
    cuerpo->setCategoryBits(CATEGORY_GUN);
    cuerpo->setDensity(1.0f);
    cuerpo->setRestitution(0.2f);
    cuerpo->setFriction(0.7);

    //Creacion del cuerpo visible (shape)
    m_vBody = new VisibleBody(posx * PPM, posy * PPM, sizex, sizey, Resources::getInstance()->armas, true);

}

void Weapon::update() {
    m_vBody->setPos(cuerpo->getPosicionX() * PPM, cuerpo->getPosicionY() * PPM);
    m_vBody->setAngle(cuerpo->getAngulo()*180);
    m_vBody->updateBody();

    if (used && !inPossession) checkIfDelete();
}

void Weapon::update(float posX, float posY) {
    cuerpo->setPosicion(posX, posY);
    m_vBody->setPos(posX * PPM, posY * PPM);
    m_vBody->setAngle(cuerpo->getAngulo()*180);
    m_vBody->updateBody();
    if (used && !inPossession) checkIfDelete();
}

void Weapon::checkIfDelete() {
    float vx = fabs(cuerpo->getVelocidadX());
    float vy = fabs(cuerpo->getVelocidadY());
    if (vx < 0.005 && vy < 0.005 && ammo == 0) {
        doDelete();
    }
}

void Weapon::doDelete() {
    for (int i = 0; i < Partida::getInstance()->worldWeapons.size(); i++) {
        Weapon* arma = Partida::getInstance()->worldWeapons.at(i);
        if (arma != NULL) {
            if (arma == this) {
                Partida::getInstance()->weapons2Delete.push_back(Partida::getInstance()->worldWeapons.at(i));
                Partida::getInstance()->worldWeapons.at(i) = NULL;
            }
        }
    }
}

int Weapon::shoot() {
    if (ammo != 0) {

        deltaClock.restartClock();
        difTime += deltaClock.getDeltaTimeAsSeconds();

        if (difTime >= shootCadence) {

            difTime = 0.0;
            if (ammo > 0) ammo--;
            Partida *partida = Partida::getInstance();

            if (!parabola) {

                float difAng = 90 / (BPS * 2);
                for (int i = 0; i < BPS / 2; i++) {
                    Bala* nuevaBala = new Bala(10, 4, cuerpo->getPosicionX() * PPM + (pSize/2.5) * dir, cuerpo->getPosicionY() * PPM, explosivo, rango, balasVisibles);
                    nuevaBala->Disparar(5 * -dir, 180 - difAng * (i + 1));
                    partida->worldBullets.insert(nuevaBala);
                }
                for (int i = 0; i < BPS / 2; i++) {
                    Bala* nuevaBala = new Bala(10, 4, cuerpo->getPosicionX() * PPM + (pSize/2.5) * dir, cuerpo->getPosicionY() * PPM, explosivo, rango, balasVisibles);
                    nuevaBala->Disparar(5 * -dir, 180 + difAng * (i + 1));
                    partida->worldBullets.insert(nuevaBala);
                }
                if (BPS % 2 != 0) {
                    Bala* nuevaBala = new Bala(10, 4, cuerpo->getPosicionX() * PPM + (pSize/2.5) * dir, cuerpo->getPosicionY() * PPM, explosivo, rango, balasVisibles);
                    nuevaBala->Disparar(5 * -dir, 180);
                    partida->worldBullets.insert(nuevaBala);
                }

            } else {
                Bala* nuevaBala = new Bala(10, 4, cuerpo->getPosicionX() * PPM + (pSize/2.5f) * dir, cuerpo->getPosicionY() * PPM, explosivo, rango, balasVisibles);
                nuevaBala->Disparar_Parabola(-dir, 160);
                partida->worldBullets.insert(nuevaBala);
            }

            if(!balasVisibles) Motorgrafico::getInstance()->getMusicPlayer()->playSound(Motorgrafico::getInstance()->getMusicPlayer()->shot);

            return recoil;
        }
    } else {
        if(!balasVisibles) Motorgrafico::getInstance()->getMusicPlayer()->playSound(Motorgrafico::getInstance()->getMusicPlayer()->emptyCartridge);
    }
    return 0;
}

void Weapon::setPossession(bool var) {
    inPossession = var;
    if (var) used = var;
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
    cuerpo->Destruir();
    delete (cuerpo);
    delete (m_vBody);
    cuerpo = NULL;
    m_vBody = NULL;
}




