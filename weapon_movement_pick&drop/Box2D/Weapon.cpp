/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   weapon.cpp
 * Author: pedro
 * 
 * Created on 16 de marzo de 2017, 20:24
 */

#include "Weapon.h"

#define WIDTH 800
#define HEIGHT 600
#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

using namespace std;
using namespace sf;

short CATEGORY_WEAPON = 0x0003;
short MASK_WEAPON = 0x0002;

Weapon::Weapon(b2World *world, sf::Vector2f size, sf::Vector2f pos, float shoot_cad, int Bps, int amm) {
    
    shootCadence = shoot_cad;
    BPS = Bps;
    m_Size = size;
    ammo = amm;

    b2BodyDef weaponBodyDef;
    weaponBodyDef.userData = this;
    weaponBodyDef.type = b2_dynamicBody;
    weaponBodyDef.position.Set(pos.x*MPP, pos.y*MPP);
    m_pBody = world->CreateBody(&weaponBodyDef);
    
    b2PolygonShape weaponBox;
    weaponBox.SetAsBox(size.x/2*MPP, size.y/2*MPP);
    
    b2FixtureDef weaponFixtureDef;
    weaponFixtureDef.shape = &weaponBox;
    weaponFixtureDef.friction = 0.2f;
    weaponFixtureDef.restitution = 0.3f;
    weaponFixtureDef.density = 1.0f;
    weaponFixtureDef.filter.categoryBits = CATEGORY_WEAPON;
    weaponFixtureDef.filter.maskBits = MASK_WEAPON;
    
    m_pBody->CreateFixture(&weaponFixtureDef);
    
    m_Shape = new sf::RectangleShape(size);
    m_Shape->setOrigin(Vector2f(size.x/2, size.y/2));
    m_Shape->setPosition(Vector2f(m_pBody->GetPosition().x, m_pBody->GetPosition().y));
    m_Shape->setFillColor(Color::White);
}

void Weapon::update() {
    b2Vec2 pos = m_pBody->GetPosition();
    m_pBody->SetTransform(pos,0);
    m_Shape->setOrigin(m_Size.x/2, m_Size.y/2);
    m_Shape->setPosition(pos.x * PPM, pos.y * PPM);
    m_Shape->setRotation((m_pBody->GetAngle()*180)/M_PI);
}

void Weapon::update(b2Vec2 pos) {
    
    m_pBody->SetTransform(pos,0);
    m_Shape->setOrigin(m_Size.x/2, m_Size.y/2);
    m_Shape->setPosition(pos.x * PPM, pos.y * PPM);
    m_Shape->setRotation((m_pBody->GetAngle()*180)/M_PI);
    
}

void Weapon::shoot(b2World *world) {
    Bala* nuevaBala = new Bala(world, Vector2f(10,10), Vector2f(m_Shape->getGlobalBounds().left, m_pBody->GetPosition().y * PPM ));
    nuevaBala->Disparar(5*dir, 180);
    listadoBalas.insert(nuevaBala);
}

void Weapon::render(sf::RenderWindow *window){
    window->draw(*m_Shape);
}

void Weapon::setPossession(bool var) {
    inPossession = var;
}

void Weapon::throwWeapon() {
    inPossession = false;
     //No funciona ni con angular impulse, ni con apply force
    //Falla en parte por el cambio de update
}

void Weapon::setDir(int i) {
    dir = i;
}





