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
    
    cuerpo = Motorfisico::getInstance()->crearCuerpo(posx, posy, sizex, sizey);
    cuerpo->setFriction(friction);
    cuerpo->setType(0);
    cuerpo->setMaskBits(MASK_SCENERY);
    cuerpo->setCategoryBits(CATEGORY_SCENERY);
    
    //Definimos parametros de SFML
    shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
    shape->setOrigin(sizex/2, sizey/2);
    shape->setPosition(sf::Vector2f(posx, posy));
    shape->setFillColor(sf::Color::Cyan);
    
}

void Platform::Render(sf::RenderWindow *window) {
    window->draw(*shape);
}

Platform::~Platform() {
}

