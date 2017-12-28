/* 
 * File:   Platform.cpp
 * Author: daniel
 * 
 * Created on 26 de marzo de 2017, 14:03
 */

#include "headerfiles/Platform.h"

Platform::Platform() {
    cuerpo = NULL;
    body = NULL;
}

Platform::Platform(const Platform& orig) {
}

Platform::Platform(float sizex, float sizey, float posx, float posy, float friction) {
    tag = "Platform";

    cuerpo = Motorfisico::getInstance()->crearCuerpo(posx, posy, sizex, sizey, this);
    cuerpo->setFriction(friction);
    cuerpo->setType(0);
    cuerpo->setMaskBits(MASK_SCENERY);
    cuerpo->setCategoryBits(CATEGORY_SCENERY);

    //Definimos parametros de SFML
    body = new VisibleBody(posx, posy, sizex, sizey, "", true);
}

VisibleBody* Platform::getBodyShape() {
    return body;
}

void Platform::Contact(void* punt, string tipo){

}

Platform::~Platform() {
    cuerpo->Destruir();
    delete(cuerpo);
    delete(body);
    cuerpo = NULL;
    body = NULL;
}

