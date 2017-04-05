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

Platform::Platform(b2World *world, sf::Vector2f size, sf::Vector2f position, float friction) {
    tag = "Platform";
    
    //Definimos parametros de BOX2D
    b2BodyDef platformBodyDef;
    platformBodyDef.userData = this;
    platformBodyDef.position.Set(position.x*MPP, position.y*MPP);
    body = world->CreateBody(&platformBodyDef);
    
    b2PolygonShape platformBox;
    platformBox.SetAsBox(size.x/2*MPP, size.y/2*MPP);
    
    b2FixtureDef platformFixtureDef;
    platformFixtureDef.shape = &platformBox;
    platformFixtureDef.friction = friction;
    platformFixtureDef.restitution = 0.01f;
    platformFixtureDef.density = 0.7f;
    platformFixtureDef.filter.categoryBits = CATEGORY_SCENERY;
    platformFixtureDef.filter.maskBits = MASK_SCENERY;
    
    body->CreateFixture(&platformFixtureDef);
    
    //Definimos parametros de SFML
    shape = new sf::RectangleShape(size);
    shape->setOrigin(size.x/2, size.y/2);
    shape->setPosition(position);
    shape->setFillColor(sf::Color::Cyan);
    
}

void Platform::Render(sf::RenderWindow *window) {
    window->draw(*shape);
}

Platform::~Platform() {
}

