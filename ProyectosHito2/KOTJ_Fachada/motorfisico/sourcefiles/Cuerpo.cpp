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
    fixtureDef.friction = 0;
    fixtureDef.restitution = 0;
    fixtureDef.density = 0;
    fixtureDef.isSensor = false;
    m_pBody->CreateFixture(&fixtureDef);
}
Cuerpo::~Cuerpo() {
}

void Cuerpo::aplicarFuerza(float x, float y){
    b2Vec2 fuerza(x,y);
    m_pBody->ApplyForceToCenter(fuerza,true);
}
void Cuerpo::setVelocidadX(float x){
    b2Vec2 vel(x,m_pBody->GetLinearVelocity().y);
    m_pBody->SetLinearVelocity(vel);
}
void Cuerpo::setVelocidadY(float y){
    b2Vec2 vel(m_pBody->GetLinearVelocity().x,y);
    m_pBody->SetLinearVelocity(vel);
}
void Cuerpo::setVelocidad(float x, float y){
    b2Vec2 vel(x,y);
    m_pBody->SetLinearVelocity(vel);
}

void Cuerpo::setAngulo(float angle){
    b2Vec2 igual = m_pBody->GetPosition();
    m_pBody->SetTransform(igual, angle);
}
//0-> Estatico 1-> Dinamico 2-> Kinetico
void Cuerpo::setType(int type){
    switch (type){
        case 0:
            m_pBody->SetType(b2_staticBody);
            break;
        
        case 1:
            m_pBody->SetType(b2_dynamicBody);
            break;
        
        case 2:    
            m_pBody->SetType(b2_kinematicBody);
            break;
    }
}
void Cuerpo::setPosicion(float x,float y){
    float igual = m_pBody->GetAngle();
    b2Vec2 pos(x,y);
    m_pBody->SetTransform(pos,igual);
}


void Cuerpo::setFriction(float fric){
    m_pBody->GetFixtureList()[0].SetFriction(fric);
}
void Cuerpo::setRestitution(float rest){
    m_pBody->GetFixtureList()[0].SetRestitution(rest);
}
void Cuerpo::setDensity(float den){
    m_pBody->GetFixtureList()[0].SetDensity(den);
}
void Cuerpo::setSensor(bool sensor){
    b2Fixture fix = m_pBody->GetFixtureList()[0];
    
    m_pBody->DestroyFixture(&fix);
    
    b2FixtureDef fix2;
    fix2.isSensor = sensor;
    fix2.density = fix.GetDensity();
    fix2.filter.categoryBits = fix.GetFilterData().categoryBits;
    fix2.filter.maskBits = fix.GetFilterData().maskBits;
    fix2.friction = fix.GetFriction();
    fix2.restitution = fix.GetRestitution();
    fix2.shape = fix.GetShape();
    fix2.userData = fix.GetUserData();
    
    m_pBody->CreateFixture(&fix2);
}

void Cuerpo::setDespertar(bool despertador){
    m_pBody->SetAwake(despertador);
}

//Se le pasa el filtro al que pertenece el objeto, tipo 0x0001
void Cuerpo::setCategoryBits(short category){
    b2Filter filter = m_pBody->GetFixtureList()[0].GetFilterData();
    
    filter.categoryBits= category;
    
    m_pBody->GetFixtureList()[0].SetFilterData(filter);
}
//Se le pasan los filtros con los que puede colisionar el objeto
void Cuerpo::setMaskBits(short mask){
    b2Filter filter = m_pBody->GetFixtureList()[0].GetFilterData();
    
    filter.maskBits = mask;
    
    m_pBody->GetFixtureList()[0].SetFilterData(filter);
}

void Cuerpo::setUserData(){
    m_pBody->SetUserData(this);
}
float Cuerpo::getAngulo(){
    return m_pBody->GetAngle();
}
float Cuerpo::getPosicionX(){
    return m_pBody->GetPosition().x;
}
float Cuerpo::getPosicionY(){
    return m_pBody->GetPosition().y;
}
float Cuerpo::getVelocidadX(){
    return m_pBody->GetLinearVelocity().x;
}
float Cuerpo::getVelocidadY(){
    return m_pBody->GetLinearVelocity().y;

}




