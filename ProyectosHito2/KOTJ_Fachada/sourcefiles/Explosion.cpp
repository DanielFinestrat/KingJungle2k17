/* 
 * File:   Explosion.cpp
 * Author: angel
 * 
 * Created on 2 de abril de 2017, 23:50
 */

#include "../motorfisico/headerfiles/Motorfisico.h"
#include "../headerfiles/Explosion.h"
#include "../headerfiles/Partida.h"

Explosion::Explosion(sf::Vector2f position, float radio, float incremento, float inicial) {
    tag = "Explosion";

    radioActual = inicial;
    radioMax = radio;
    incrementoRadio = incremento;

    difTime = 0;
    
    cuerpo = Motorfisico::getInstance()->crearCuerpoCircular(position.x, position.y, radio, this);
    cuerpo->setMaskBits(MASK_EXPLOSION);
    cuerpo->setCategoryBits(CATEGORY_EXPLOSION);
    cuerpo->setDensity(0.7f);
    cuerpo->setType(2);

    m_Shape = new sf::CircleShape(inicial * PPM);
    m_Shape->setOrigin(radioActual * PPM, radioActual * PPM);
    m_Shape->setPosition(sf::Vector2f(cuerpo->getPosicionX() * PPM, cuerpo->getPosicionY() * PPM));
    m_Shape->setFillColor(sf::Color::White);

}

void Explosion::Update() {
    if (radioActual < radioMax) {

        dt = deltaClock.restart();
        difTime += dt.asSeconds();

        if (difTime >= 0.02) {
            difTime = 0;
            radioActual = radioActual + incrementoRadio;

            cuerpo->setRadio(radioActual);
            float angle = cuerpo->getAngulo();
            float posX = cuerpo->getPosicionX();
            float posY = cuerpo->getPosicionY();

            m_Shape->setRadius(radioActual * PPM);
            m_Shape->setOrigin(radioActual * PPM, radioActual * PPM);
            m_Shape->setPosition(posX * PPM, posY * PPM);
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
    cuerpo->Destruir();
    delete cuerpo;
    cuerpo = NULL;
    delete m_Shape;
    m_Shape = NULL;
}
