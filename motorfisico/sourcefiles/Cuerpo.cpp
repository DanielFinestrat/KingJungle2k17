/* 
 * File:   Cuerpo.cpp
 * Author: youjair
 * 
 * Created on 5 de abril de 2017, 19:18
 */

#include "../headerfiles/Cuerpo.h"

#include <stdio.h>
#include <math.h>
#include <iostream>

#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

Cuerpo::Cuerpo(b2World *world, b2Vec2 pos, b2Vec2 size, float angle, Entidad* data) {
    b2BodyDef body;
    body.type = b2_dynamicBody;
    body.position.Set(pos.x*MPP, pos.y * MPP);
    body.angle = angle;
    body.fixedRotation = true;
    m_pBody = world->CreateBody(&body);

    b2PolygonShape box;
    box.SetAsBox((size.x / 2) * MPP, (size.y / 2) * MPP);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.01f;
    fixtureDef.isSensor = false;
    m_pBody->CreateFixture(&fixtureDef);
    
    m_pBody->SetUserData(data);
}

Cuerpo::~Cuerpo() {
    //delete(m_pBody);
    m_pBody = NULL;
}

void Cuerpo::Destruir(){
    m_pBody->GetWorld()->DestroyBody(m_pBody);
}

void Cuerpo::aplicarFuerza(float x, float y) {
    b2Vec2 fuerza(x, y);
    m_pBody->ApplyForceToCenter(fuerza, true);
}

void Cuerpo::setVelocidadX(float x) {
    b2Vec2 vel(x, m_pBody->GetLinearVelocity().y);
    m_pBody->SetLinearVelocity(vel);
}

void Cuerpo::setVelocidadY(float y) {
    b2Vec2 vel(m_pBody->GetLinearVelocity().x, y);
    m_pBody->SetLinearVelocity(vel);
}

void Cuerpo::setVelocidad(float x, float y) {
    b2Vec2 vel(x, y);
    m_pBody->SetLinearVelocity(vel);
}

void Cuerpo::setAngulo(float angle) {
    b2Vec2 igual = m_pBody->GetPosition();
    m_pBody->SetTransform(igual, angle);
}

void Cuerpo::setTamanyo(float x, float y){
    b2PolygonShape box;
    box.SetAsBox((x / 2) * MPP, (y / 2) * MPP);
    
    b2Fixture fix = m_pBody->GetFixtureList()[0];

    b2FixtureDef fix2;
    fix2.shape = &box;
    fix2.friction = fix.GetFriction();
    fix2.density = fix.GetDensity();
    fix2.isSensor = fix.IsSensor();
    fix2.filter.categoryBits = fix.GetFilterData().categoryBits;
    fix2.filter.maskBits = fix.GetFilterData().maskBits;
    fix2.restitution = fix.GetRestitution();
    fix2.userData = fix.GetUserData();

    m_pBody->CreateFixture(&fix2);
}

/**0-> Estatico 1-> Dinamico 2-> Kinetico*/
void Cuerpo::setType(int type) {
    switch (type) {
        case 0:
            m_pBody->SetType(b2_staticBody);
            m_pBody->SetAwake(true);
            break;
        case 1:
            m_pBody->SetType(b2_dynamicBody);
            m_pBody->SetAwake(true);
            break;
        case 2:
            m_pBody->SetType(b2_kinematicBody);
            m_pBody->SetAwake(true);
            break;
    }
}

void Cuerpo::setPosicion(float x, float y) {
    float igual = m_pBody->GetAngle();
    b2Vec2 pos(x, y);
    m_pBody->SetTransform(pos, igual);
}

void Cuerpo::setFriction(float fric) {
    b2Fixture fix = m_pBody->GetFixtureList()[0];

    b2FixtureDef fix2;
    fix2.friction = fric;
    fix2.density = fix.GetDensity();
    fix2.isSensor = fix.IsSensor();
    fix2.filter.categoryBits = fix.GetFilterData().categoryBits;
    fix2.filter.maskBits = fix.GetFilterData().maskBits;
    fix2.restitution = fix.GetRestitution();
    fix2.shape = fix.GetShape();
    fix2.userData = fix.GetUserData();

    m_pBody->CreateFixture(&fix2);
}

void Cuerpo::setRestitution(float rest) {
    b2Fixture fix = m_pBody->GetFixtureList()[0];

    b2FixtureDef fix2;
    fix2.restitution = rest;
    fix2.density = fix.GetDensity();
    fix2.isSensor = fix.IsSensor();
    fix2.filter.categoryBits = fix.GetFilterData().categoryBits;
    fix2.filter.maskBits = fix.GetFilterData().maskBits;
    fix2.friction = fix.GetFriction();    
    fix2.shape = fix.GetShape();
    fix2.userData = fix.GetUserData();

    m_pBody->CreateFixture(&fix2);
}

void Cuerpo::setDensity(float den) {
    b2Fixture fix = m_pBody->GetFixtureList()[0];

    b2FixtureDef fix2;
    fix2.density = den;
    fix2.isSensor = fix.IsSensor();
    fix2.filter.categoryBits = fix.GetFilterData().categoryBits;
    fix2.filter.maskBits = fix.GetFilterData().maskBits;
    fix2.friction = fix.GetFriction();
    fix2.restitution = fix.GetRestitution();
    fix2.shape = fix.GetShape();
    fix2.userData = fix.GetUserData();

    m_pBody->CreateFixture(&fix2);
}

void Cuerpo::setSensor(bool sensor) {
    m_pBody->GetFixtureList()[0].SetSensor(sensor);
}

void Cuerpo::setActive(bool active){
    m_pBody->SetActive(active);
}

void Cuerpo::setAwake(bool awake){
    m_pBody->SetAwake(awake);
}

bool Cuerpo::getActive(){
    return(m_pBody->IsActive());
}

void Cuerpo::setDespertar(bool despertador) {
    m_pBody->SetAwake(despertador);
}

//Se le pasa el filtro al que pertenece el objeto, tipo 0x0001
void Cuerpo::setCategoryBits(short category) {
    b2Filter filter = m_pBody->GetFixtureList()[0].GetFilterData();
    filter.categoryBits = category;
    m_pBody->GetFixtureList()[0].SetFilterData(filter);
}

//Se le pasan los filtros con los que puede colisionar el objeto
void Cuerpo::setMaskBits(short mask) {
    b2Filter filter = m_pBody->GetFixtureList()[0].GetFilterData();
    filter.maskBits = mask;
    m_pBody->GetFixtureList()[0].SetFilterData(filter);
}

void Cuerpo::setGravityScale(float gravityScale){
    m_pBody->SetGravityScale(gravityScale);
}

void Cuerpo::setUserData(Entidad* data) {
    m_pBody->SetUserData(data);
}

float Cuerpo::getAngulo() {
    return m_pBody->GetAngle();
}

float Cuerpo::getPosicionX() {
    return m_pBody->GetPosition().x;
}

float Cuerpo::getPosicionY() {
    return m_pBody->GetPosition().y;
}

float Cuerpo::getVelocidadX() {
    return m_pBody->GetLinearVelocity().x;
}

float Cuerpo::getVelocidadY() {
    return m_pBody->GetLinearVelocity().y;
}