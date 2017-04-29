
/* 
 * File:   Fondo.cpp
 * Author: danielfinestrat
 * 
 * Created on 29 de abril de 2017, 10:17
 */

#include "../headerfiles/Fondo.h"
#include "../headerfiles/Motorgrafico.h"

Fondo::Fondo(string ruta) {
    imagenFondo = new Sprite();
    imagenFondo->setTexture(Resources::getInstance()->getTexture(ruta));
    
    float w = imagenFondo->getLocalBounds().width/2;
    float h = imagenFondo->getLocalBounds().height/2;
    imagenFondo->setOrigin(w, h);
}

void Fondo::Update(){
    float x = Motorgrafico::getInstance()->getCameraPositionX();
    float y = Motorgrafico::getInstance()->getCameraPositionY();
    setPosition(x, y);
}

void Fondo::setPosition(float x, float y){
    imagenFondo->setPosition(x, y);
}

void Fondo::Render(){
    Motorgrafico::getInstance()->draw(*imagenFondo);
}

Fondo::~Fondo() {
}

