/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Trampa.cpp
 * Author: youjair
 * 
 * Created on 26 de marzo de 2017, 18:36
 */

#include "Trampa.h"
#include "Box2D/Box2D.h"


#define WIDTH 800
#define HEIGHT 600
#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

using namespace std;
using namespace sf;




Trampa::Trampa(b2World *world, sf::Vector2f size, sf::Vector2f pos, int type ) {
    id = type;
    estado = false;
    roto = false; 
    
    b2BodyDef trapBody;
    trapBody.type = b2_dynamicBody;
    trapBody.position.Set(pos.x, pos.y);
    trapBody.angle = 0;
    
    b2Body* dynamicBody = world->CreateBody(&trapBody);
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);
    
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    dynamicBody->CreateFixture(&boxFixtureDef);
    
}

Trampa::Trampa(const Trampa& orig) {
}

Trampa::~Trampa() {
}
void Trampa::activar(){
    if(estado ==false) estado = true;
    std::cout << "activada" << std::endl;
}
void Trampa::desactivar(){
    if(estado == true) estado = false;
    std::cout << "desactivada" << std::endl;
}
int Trampa::getID(){
    return id;
}
bool Trampa::getEstado(){
    return estado;
}

