/* 
 * File:   Explosion.cpp
 * Author: angel
 * 
 * Created on 2 de abril de 2017, 23:50
 */

#include "motorfisico/headerfiles/Motorfisico.h"
#include "headerfiles/Explosion.h"
#include "headerfiles/Partida.h"
#include <stdio.h>
#include <iostream>
#include <PI.h>

Explosion::Explosion(float posx, float posy, float radio, float incremento, float inicial) {
    tag = "Explosion";
    
    radioActual = inicial;
    radioMax = radio;
    incrementoRadio = incremento;
    difTime = 0;
    
    cuerpo = Motorfisico::getInstance()->crearCuerpoCircular(posx, posy, inicial, this);
    cuerpo->setMaskBits(MASK_EXPLOSION);
    cuerpo->setCategoryBits(CATEGORY_EXPLOSION);
    cuerpo->setDensity(0.7f);
    cuerpo->setType(2);
    
    shape = new VisibleBody(cuerpo->getPosicionX() * PPM, cuerpo->getPosicionY() * PPM,inicial * PPM,"");
    shape->setTex(Resources::getInstance()->explosion);
    shape->setCircleOrigin(radioActual * PPM, radioActual * PPM);

}

void Explosion::Update() {
    if (radioActual < radioMax) {

        deltaClock.restartClock();
        difTime += deltaClock.getDeltaTimeAsSeconds();

        if (difTime >= 0.02) {
            difTime = 0;
            radioActual = radioActual + incrementoRadio;

            cuerpo->setRadio(radioActual);
            float angle = cuerpo->getAngulo();
            float posX = cuerpo->getPosicionX();
            float posY = cuerpo->getPosicionY();

            shape->setCircleRadius(radioActual * PPM);
            shape->setCircleOrigin(radioActual * PPM, radioActual * PPM);
            shape->setCirclePos(posX * PPM, posY * PPM);
            shape->setCircleRot((angle * 180) / M_PI);
        }
    } else {
        Partida* partida = Partida::getInstance();
        partida->explo2Delete.insert(this);
    }
}

VisibleBody* Explosion::getBodyShape(){
    return shape;
}

void Explosion::Contact(void* punt, string tipo){

}

Explosion::~Explosion() {
    cuerpo->Destruir();
    delete cuerpo;
    cuerpo = NULL;
    delete shape;
    shape = NULL;
}
