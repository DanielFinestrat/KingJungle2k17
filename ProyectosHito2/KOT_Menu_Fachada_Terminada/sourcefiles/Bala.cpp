/* 
 * File:   Bala.cpp
 * Author: angel
 * 
 * Created on 16 de marzo de 2017, 20:43
 */

#include "../headerfiles/Bala.h"
#include "../headerfiles/Partida.h"

using namespace std;

Bala::Bala(float x, float y, float posx, float posy, bool explo) {
    tag = "Bala";
    explosion = explo;

    cuerpo = Motorfisico::getInstance()->crearCuerpo(0, 0, x, y, this);
    cuerpo->setPosicion(posx * MPP, posy * MPP);
    cuerpo->setMaskBits(MASK_BULLET);
    cuerpo->setCategoryBits(CATEGORY_BULLET);
    cuerpo->setDensity(0.7f);
    
    shape = new VisibleBody(cuerpo->getPosicionX() * PPM, cuerpo->getPosicionY() * PPM,x,y,"");
    
}

void Bala::Update_Shape() {
    
    Partida *partida = Partida::getInstance();
    
    float posX = cuerpo->getPosicionX();
    float posY = cuerpo->getPosicionY();
    float angle = cuerpo->getAngulo();

    //Se comprueba si las balas salen de la pantalla
    if (posX < 0 - screenWidth || posX > screenWidth * 2  * MPP || posY > screenHeight * 2 * MPP) {
        partida->bullets2Delete.insert(this);
    }

    float vx = cuerpo->getVelocidadX();
    float vy = cuerpo->getVelocidadY();

    double a = atan(vy / vx) * (180 / M_PI);     

    shape->setPos(posX * PPM, posY * PPM);
    shape->setRot(a);
}

void Bala::Disparar_Parabola(float fuerza, float angulo) {
    cuerpo->aplicarFuerza(fuerza * cos(angulo * 3.14 / 180.0f), -1 * fabs(fuerza) * sin(angulo * 3.14 / 180.0f)); 
}

void Bala::Disparar(float velocidad, float angulo) {
    shape->setRot(-angulo);
    
    cuerpo->setVelocidad(velocidad * cos(angulo * 3.14 / 180.0f), -velocidad * sin(angulo * 3.14 / 180.0f));
    cuerpo->setAngulo(-angulo);
    cuerpo->setGravityScale(0);
}

VisibleBody* Bala::getBodyShape(){
    return shape;
}

//Hacer un delete de cada objeto que se ha creado con un New y luego igualarlo a NULL
Bala::~Bala() {
    cuerpo->Destruir();
    delete cuerpo;
    cuerpo = NULL;
    delete shape;
    shape = NULL;
}





