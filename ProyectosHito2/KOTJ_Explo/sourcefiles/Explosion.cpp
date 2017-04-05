/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Explosion.cpp
 * Author: angel
 * 
 * Created on 2 de abril de 2017, 23:50
 */

#include "../headerfiles/Explosion.h"
#include "../headerfiles/Partida.h"

Explosion::Explosion(b2World *mundo, sf::Vector2f position, float radio, float incremento, float inicial) {
    tag = "Explosion";

    radioActual = inicial;
    radioMax = radio;
    incrementoRadio = incremento;

    difTime = 0;

    b2BodyDef exploBodyDef;
    exploBodyDef.userData = this;
    exploBodyDef.type = b2_staticBody;
    exploBodyDef.position.Set(position.x*MPP, position.y * MPP);
    m_pBody = mundo->CreateBody(&exploBodyDef);

    b2CircleShape exploCircle;
    exploCircle.m_p.Set(inicial, inicial);
    exploCircle.m_radius = inicial;

    b2FixtureDef exploFixtureDef;
    exploFixtureDef.shape = &exploCircle;
    exploFixtureDef.friction = 0.2f;
    exploFixtureDef.restitution = 0.3f;
    exploFixtureDef.density = 0.7f;
    exploFixtureDef.filter.categoryBits = CATEGORY_EXPLOSION;
    exploFixtureDef.filter.maskBits = MASK_EXPLOSION;

    m_pBody->CreateFixture(&exploFixtureDef);

    m_Shape = new sf::CircleShape(inicial * PPM);
    m_Shape->setOrigin(radioActual * PPM, radioActual * PPM);
    m_Shape->setPosition(sf::Vector2f(m_pBody->GetPosition().x*PPM, m_pBody->GetPosition().y * PPM));
    m_Shape->setFillColor(sf::Color::White);

}

void Explosion::Update() {
    if (radioActual < radioMax) {

        dt = deltaClock.restart();
        difTime += dt.asSeconds();

        if (difTime >= 0.02) {
            difTime = 0;
            radioActual = radioActual + incrementoRadio;

            b2Fixture *fixtureA = m_pBody->GetFixtureList();
            m_pBody->DestroyFixture(fixtureA);

            b2CircleShape circleShape;
            circleShape.m_radius = radioActual;

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &circleShape;
            fixtureDef.friction = 0.2f;
            fixtureDef.restitution = 0.3f;
            fixtureDef.density = 0.7f;
            fixtureDef.filter.categoryBits = CATEGORY_EXPLOSION;
            fixtureDef.filter.maskBits = MASK_EXPLOSION;

            m_pBody->CreateFixture(&fixtureDef);

            float angle = m_pBody->GetAngle();
            b2Vec2 pos = m_pBody->GetPosition();

            m_Shape->setRadius(radioActual * PPM);
            m_Shape->setOrigin(radioActual * PPM, radioActual * PPM);
            m_Shape->setPosition(pos.x * PPM, pos.y * PPM);
            m_Shape->setRotation((angle * 180) / M_PI);
        }
    } else {
        Partida* partida = Partida::getInstance();
        partida->explo2Delete.insert(this);
    }
}

void Explosion::Render(sf::RenderWindow *window) {
    window->draw(*m_Shape);
}

Explosion::~Explosion() {
    m_pBody->GetWorld()->DestroyBody(m_pBody);
    delete m_Shape;
    m_Shape = NULL;
}
