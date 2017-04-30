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




#define WIDTH 800
#define HEIGHT 600
#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL
#define VELTRAP 5           //Velocidad que tendra la trampa

using namespace std;
using namespace sf;




//Trampa::Trampa(b2World *world, sf::Vector2f size, sf::Vector2f pos, int type, float angle ) {
Trampa::Trampa(MotorFisico *world, int sizeX, int sizeY, int posX, int posY, int type, float angle){
    id = type;
    estado = false;
    roto = false; 
    m_Size = size;
    iniPosX = posX;
    iniPosY = posY;
    contact = false;
    
    
    b2BodyDef trapBody;
    trapBody.userData = this;
    trapBody.type = b2_kinematicBody;
    trapBody.position.Set(pos.x*MPP, pos.y*MPP);
    trapBody.angle = angle;
    
    m_pBody = world->CreateBody(&trapBody);
    
    b2PolygonShape trapBox;
    trapBox.SetAsBox(size.x/2*MPP, size.y/2*MPP);
    
    b2FixtureDef trapFixtureDef;
    trapFixtureDef.shape = &trapBox;
    trapFixtureDef.friction = 0.2f;
    trapFixtureDef.restitution = 0.3f;
    trapFixtureDef.density = 0.4f;
    trapFixtureDef.isSensor = true;
    trapFixtureDef.filter.categoryBits = 0x0001;
    trapFixtureDef.filter.maskBits = 0x0004;
    m_pBody->CreateFixture(&trapFixtureDef);
    
    m_Shape =  new sf::RectangleShape(size);
    m_Shape->setOrigin(size.x/2, size.y/2);
    m_Shape->setPosition(sf::Vector2f(m_pBody->GetPosition().x*PPM, m_pBody->GetPosition().y*PPM));
    m_Shape->setFillColor(Color::White);
}

Trampa::Trampa(const Trampa& orig) {
}

Trampa::~Trampa() {
}
void Trampa::activar(){
    if(estado ==false){ estado = true;
    std::cout << "activada" << std::endl;
    
    b2Vec2 vel = m_pBody->GetLinearVelocity();
    vel.y = -VELTRAP;
    m_pBody->SetLinearVelocity(vel);
    
    
    
    }
    
}
void Trampa::desactivar(){
    if(estado == true){ estado = false;
    std::cout << "desactivada"<< std:: endl;
    b2Vec2 vel = m_pBody->GetLinearVelocity();
    vel.y = VELTRAP;
    m_pBody->SetLinearVelocity(vel);
    }
}
int Trampa::getID(){
    return id;
}
sf::RectangleShape Trampa::updateShape(){
    float angle = m_pBody->GetAngle();
    b2Vec2 pos = m_pBody->GetPosition();
            
    m_Shape->setPosition(pos.x * PPM, pos.y * PPM);
    m_Shape->setRotation(angle);
    
    if(iniPos.y >= pos.y*PPM+m_Size.y && m_pBody->GetLinearVelocity().y < 0){
        b2Vec2 vel = m_pBody->GetLinearVelocity();
        vel.y = 0;
        m_pBody->SetLinearVelocity(vel);
    } else if(iniPos.y <= pos.y*PPM && m_pBody->GetLinearVelocity().y > 0){
        b2Vec2 vel = m_pBody->GetLinearVelocity();
        vel.y = 0;
        m_pBody->SetLinearVelocity(vel);
    }
    
    return *m_Shape;
}
bool Trampa::getEstado(){
    return estado;
}
void Trampa::render(sf::RenderWindow *window){
    window->draw(*m_Shape);
}
void Trampa::startContact(){
    contact = true;
    std::cout<<"Has muerto."<<std::endl;
}
void Trampa::endContact(){
    contact = false;
}
