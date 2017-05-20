/* 
 * File:   CuerpoCircular.cpp
 * Author: danielfinestrat
 * 
 * Created on 24 de abril de 2017, 12:03
 */

#include "../headerfiles/CuerpoCircular.h"

#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

CuerpoCircular::CuerpoCircular(b2World *world, b2Vec2 pos, float radio, float angle, Entidad* data) {
    b2BodyDef body;
    body.type = b2_dynamicBody;
    body.position.Set(pos.x*MPP, pos.y * MPP);
    body.angle = angle;
    body.fixedRotation = true;

    m_pBody = world->CreateBody(&body);
    b2CircleShape exploCircle;
    exploCircle.m_p.Set(radio, radio);
    exploCircle.m_radius = radio;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &exploCircle;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.01f;
    fixtureDef.isSensor = false;
    m_pBody->CreateFixture(&fixtureDef);

    m_pBody->SetUserData(data);
}

CuerpoCircular::~CuerpoCircular() {
}

void CuerpoCircular::Destruir(){
    m_pBody->GetWorld()->DestroyBody(m_pBody);
}

void CuerpoCircular::aplicarFuerza(float x, float y) {
    b2Vec2 fuerza(x, y);
    m_pBody->ApplyForceToCenter(fuerza, true);
}

void CuerpoCircular::setVelocidadX(float x) {
    b2Vec2 vel(x, m_pBody->GetLinearVelocity().y);
    m_pBody->SetLinearVelocity(vel);
}

void CuerpoCircular::setVelocidadY(float y) {
    b2Vec2 vel(m_pBody->GetLinearVelocity().x, y);
    m_pBody->SetLinearVelocity(vel);
}

void CuerpoCircular::setVelocidad(float x, float y) {
    b2Vec2 vel(x, y);
    m_pBody->SetLinearVelocity(vel);
}

void CuerpoCircular::setAngulo(float angle) {
    b2Vec2 igual = m_pBody->GetPosition();
    m_pBody->SetTransform(igual, angle);
}

void CuerpoCircular::setRadio(float radio){
    b2CircleShape circleShape;
    circleShape.m_radius = radio;
    
    b2Fixture fix = m_pBody->GetFixtureList()[0];

    b2FixtureDef fix2;
    fix2.shape = &circleShape;
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
void CuerpoCircular::setType(int type) {
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

void CuerpoCircular::setPosicion(float x, float y) {
    float igual = m_pBody->GetAngle();
    b2Vec2 pos(x, y);
    m_pBody->SetTransform(pos, igual);
}

void CuerpoCircular::setFriction(float fric) {
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

void CuerpoCircular::setRestitution(float rest) {
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

void CuerpoCircular::setDensity(float den) {
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

void CuerpoCircular::setSensor(bool sensor) {
    b2Fixture fix = m_pBody->GetFixtureList()[0];

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

void CuerpoCircular::setActive(bool active){
    m_pBody->SetActive(active);
}

void CuerpoCircular::setAwake(bool awake){
    m_pBody->SetAwake(awake);
}

bool CuerpoCircular::getActive(){
    return(m_pBody->IsActive());
}

void CuerpoCircular::setDespertar(bool despertador) {
    m_pBody->SetAwake(despertador);
}

//Se le pasa el filtro al que pertenece el objeto, tipo 0x0001
void CuerpoCircular::setCategoryBits(short category) {
    b2Filter filter = m_pBody->GetFixtureList()[0].GetFilterData();
    filter.categoryBits = category;
    m_pBody->GetFixtureList()[0].SetFilterData(filter);
}

//Se le pasan los filtros con los que puede colisionar el objeto
void CuerpoCircular::setMaskBits(short mask) {
    b2Filter filter = m_pBody->GetFixtureList()[0].GetFilterData();
    filter.maskBits = mask;
    m_pBody->GetFixtureList()[0].SetFilterData(filter);
}

void CuerpoCircular::setGravityScale(float gravityScale){
    m_pBody->SetGravityScale(gravityScale);
}

void CuerpoCircular::setUserData(Entidad* data) {
    m_pBody->SetUserData(data);
}

float CuerpoCircular::getAngulo() {
    return m_pBody->GetAngle();
}

float CuerpoCircular::getPosicionX() {
    return m_pBody->GetPosition().x;
}

float CuerpoCircular::getPosicionY() {
    return m_pBody->GetPosition().y;
}

float CuerpoCircular::getVelocidadX() {
    return m_pBody->GetLinearVelocity().x;
}

float CuerpoCircular::getVelocidadY() {
    return m_pBody->GetLinearVelocity().y;
}

