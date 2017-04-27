/* 
 * File:   Explosion.cpp
 * Author: angel
 * 
 * Created on 2 de abril de 2017, 23:50
 */

#include "../motorfisico/headerfiles/Motorfisico.h"
#include "../headerfiles/Explosion.h"
#include "../headerfiles/Partida.h"

Explosion::Explosion(float posx, float posy, float radio, float incremento, float inicial) {
    tag = "Explosion";

    radioActual = inicial;
    radioMax = radio;
    incrementoRadio = incremento;

    difTime = 0;
    
    cuerpo = Motorfisico::getInstance()->crearCuerpoCircular(posx, posy, radio, this);
    cuerpo->setMaskBits(MASK_EXPLOSION);
    cuerpo->setCategoryBits(CATEGORY_EXPLOSION);
    cuerpo->setDensity(0.7f);
    cuerpo->setType(2);

    figure = new VisibleFigure(inicial * PPM);
    figure->circShapeSetOrigin(radioActual * PPM, radioActual * PPM);
    figure->circShapeSetPosition(cuerpo->getPosicionX() * PPM, cuerpo->getPosicionY() * PPM);
    figure->circShapeSetFillColor(255,255,255,255);

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

            figure->circShapeSetRadius(radioActual * PPM);
            figure->circShapeSetOrigin(radioActual * PPM, radioActual * PPM);
            figure->circShapeSetPosition(posX * PPM, posY * PPM);
            figure->circShapeSetRotation((angle * 180) / M_PI);
        }
    } else {
        Partida* partida = Partida::getInstance();
        partida->explo2Delete.insert(this);
    }
}

Explosion::~Explosion() {
    cuerpo->Destruir();
    delete cuerpo;
    cuerpo = NULL;
    delete figure;
    figure = NULL;
}
