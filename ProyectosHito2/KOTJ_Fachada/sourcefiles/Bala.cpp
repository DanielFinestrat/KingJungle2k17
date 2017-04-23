/* 
 * File:   Bala.cpp
 * Author: angel
 * 
 * Created on 16 de marzo de 2017, 20:43
 */

#include "../headerfiles/Bala.h"
#include "../headerfiles/Partida.h"

using namespace std;
using namespace sf;

Bala::Bala(sf::Vector2f size, sf::Vector2f position, bool explo) {
    tag = "Bala";
    explosion = explo;
    m_Size = size;

    cuerpo = Motorfisico::getInstance()->crearCuerpo(0, 0, size.x, size.y);
    cuerpo->setPosicion(position.x * MPP, position.y * MPP);
    cuerpo->setMaskBits(MASK_BULLET);
    cuerpo->setCategoryBits(CATEGORY_BULLET);
    cuerpo->setDensity(0.7f);
    cuerpo->setFriction(0.2f);
    cuerpo->setRestitution(0.0f);

    m_Shape = new sf::RectangleShape(size);
    m_Shape->setOrigin(size.x / 2, size.y / 2);
    m_Shape->setPosition(sf::Vector2f(cuerpo->getPosicionX() * PPM, cuerpo->getPosicionY() * PPM));
    m_Shape->setFillColor(sf::Color::Yellow);
}

void Bala::Update_Shape() {
    
    Partida *partida = Partida::getInstance();
    
    float posX = cuerpo->getPosicionX();
    float posY = cuerpo->getPosicionY();
    float angle = cuerpo->getAngulo();

    //Se comprueba si las balas salen de la pantalla
    if (posX < 0 - screenWidth || posX > screenWidth * 2  * MPP || posY > screenHeight * 2 * MPP) {
        partida->bullets2Delete.insert(this);
    }

    float vx = cuerpo->getVelocidadX();
    float vy = cuerpo->getVelocidadY();

    double a = atan(vy / vx) * (180 / M_PI);     

    m_Shape->setPosition(posX * PPM, posY * PPM);
    m_Shape->setRotation(a);
}

void Bala::Disparar_Parabola(float fuerza, float angulo) {
    cuerpo->aplicarFuerza(fuerza * cos(angulo * 3.14 / 180.0f), -1 * fabs(fuerza) * sin(angulo * 3.14 / 180.0f)); 
}

void Bala::Disparar(float velocidad, float angulo) {
    cuerpo->setVelocidad(velocidad * cos(angulo * 3.14 / 180.0f), -velocidad * sin(angulo * 3.14 / 180.0f));
    
    m_Shape->rotate(-angulo);
    cuerpo->setAngulo(-angulo);    
}

void Bala::Render(sf::RenderWindow *window) {
    window->draw(*m_Shape);
}

Bala::~Bala() {
    cout<<"eliminar bala"<<endl;
    cuerpo->Destruir();
    delete cuerpo;
    cuerpo = NULL;
    delete m_Shape;
    m_Shape = NULL;
    //Hacer un delete de cada objeto que se ha creado con un New y luego igualarlo a NULL
}





