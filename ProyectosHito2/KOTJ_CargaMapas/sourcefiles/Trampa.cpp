
/* 
 * File:   Trampa.cpp
 * Author: youjair
 * 
 * Created on 26 de marzo de 2017, 18:36
 */

#include "../headerfiles/Trampa.h"
#include "../motorfisico/headerfiles/Motorfisico.h"

#define VELTRAP 5 //Velocidad que tendra la trampa

using namespace std;
using namespace sf;

Trampa::Trampa(int sizeX, int sizeY, int posX, int posY, int type, float angle) {
    tag = "Trampa";
    id = type;
    estado = false;
    roto = false;
    m_SizeX = sizeX;
    m_SizeY = sizeY;
    iniPosX = posX;
    iniPosY = posY;
    contact = false;

    cuerpo = Motorfisico::getInstance()->crearCuerpo(posX, posY, sizeX, sizeY, angle, this);
    cuerpo->setType(2);
    cuerpo->setSensor(true);

    m_Shape = new VisibleBody(posX, posY, sizeX, sizeY, "", false);
}

Trampa::Trampa(const Trampa& orig) {
}

Trampa::~Trampa() {
}

void Trampa::activar() {
    int velY;

    if (!estado) {
        estado = true;
        velY = -VELTRAP;
        cuerpo->setVelocidadY(velY);
    }

}

void Trampa::desactivar() {
    int velY;

    if (estado) {
        estado = false;
        velY = VELTRAP;
        cuerpo->setVelocidadY(velY);
    }
}

int Trampa::getID() {
    return id;
}

VisibleBody* Trampa::updateShape() {
    float angle = cuerpo->getAngulo();
    int posX = cuerpo->getPosicionX();
    int posY = cuerpo->getPosicionY();
    int velY;

    m_Shape->setPos(posX*PPM, posY * PPM);
    m_Shape->setAngle(angle);

    if (iniPosY >= posY * PPM + m_SizeY && cuerpo->getVelocidadY() < 0) {
        velY = 0;
        cuerpo->setVelocidadY(velY);
    } else if (iniPosY <= posY * PPM && cuerpo->getVelocidadY() > 0) {
        velY = 0;
        cuerpo->setVelocidadY(velY);
    }

    return m_Shape;
}

bool Trampa::getEstado() {
    return estado;
}

void Trampa::startContact() {
    contact = true;
    std::cout << "Has muerto." << std::endl;
}

void Trampa::endContact() {
    contact = false;
}

Cuerpo* Trampa::getCuerpo(){
    return(this->cuerpo);
}
