/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cuerpo.cpp
 * Author: youjair
 * 
 * Created on 5 de abril de 2017, 19:18
 */

#include "../headerfiles/Cuerpo.h"

#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

Cuerpo::Cuerpo(b2World *world, b2Vec2 pos, b2Vec2 size, float angle) {
    b2BodyDef body;
    body.position.Set(pos.x*MPP, pos.y*MPP);
    body.angle = angle;
    
    m_pBody = world->CreateBody(&body);
    
    b2PolygonShape box;
    box.SetAsBox(size.x/2*MPP, size.y/2*MPP);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.3f;
    fixtureDef.density = 0.4f;
    fixtureDef.isSensor = true;
    fixtureDef.filter.categoryBits = 0x0001;
    fixtureDef.filter.maskBits = 0x0004;
    m_pBody->CreateFixture(&fixtureDef);
}
Cuerpo::~Cuerpo() {
}

void Cuerpo::setAngulo(float angle){
    b2Vec2 igual = m_pBody->GetPosition();
    m_pBody->SetTransform(igual, angle);
}
void Cuerpo::setTamanyo(float x, float y){
    m_pBody->GetFixtureList()[0];
    
}
void Cuerpo::setPosicion(float x,float y){
    
}

/*float Cuerpo::getAngulo(){
    return m_pBody->GetAngle();
}
float Cuerpo::getPosicionX(){
    
}
float Cuerpo::getPosicionY(){
    
}
void Cuerpo::setUserData(){
    
}*/



