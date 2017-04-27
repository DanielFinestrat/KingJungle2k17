/* 
 * File:   Platform.cpp
 * Author: daniel
 * 
 * Created on 26 de marzo de 2017, 14:03
 */

#include "../headerfiles/Platform.h"

Platform::Platform() {
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
    figure = new VisibleFigure(sizex, sizey);
    figure->rectShapeSetOrigin(sizex/2, sizey/2);
    figure->rectShapeSetPosition(posx, posy);
    figure->rectShapeSetFillColor(0,0,255,255);
}

VisibleFigure* Platform::getFigure(){
    return figure;
}


Platform::~Platform() {
}

