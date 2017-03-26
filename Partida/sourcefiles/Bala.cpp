/* 
 * File:   Bala.cpp
 * Author: angel
 * 
 * Created on 16 de marzo de 2017, 20:43
 */

#include "../headerfiles/Bala.h"


#define WIDTH 800
#define HEIGHT 600
#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

using namespace std;
using namespace sf;

Bala::Bala(b2World *mundo, sf::Vector2f size, sf::Vector2f position) {

    m_Size = size;

    b2BodyDef balaBodyDef;
    balaBodyDef.userData = this;
    balaBodyDef.type = b2_dynamicBody;
    balaBodyDef.position.Set(position.x*MPP, position.y * MPP);
    m_pBody = mundo->CreateBody(&balaBodyDef);

    b2PolygonShape balaBox;
    balaBox.SetAsBox(size.x / 2 * MPP, size.y / 2 * MPP);

    b2FixtureDef balaFixtureDef;
    balaFixtureDef.shape = &balaBox;
    balaFixtureDef.friction = 0.2f;
    balaFixtureDef.restitution = 0.3f;
    balaFixtureDef.density = 0.7f;
    balaFixtureDef.filter.categoryBits = 0x0001;
    balaFixtureDef.filter.maskBits = 0x0002;

    m_pBody->CreateFixture(&balaFixtureDef);

    m_Shape = new sf::RectangleShape(size);
    m_Shape->setOrigin(size.x / 2, size.y / 2);
    m_Shape->setPosition(sf::Vector2f(m_pBody->GetPosition().x*PPM, m_pBody->GetPosition().y * PPM));
    m_Shape->setFillColor(Color::White);
}

void Bala::Update_Shape(set<Bala*> &balasAEliminar) {
    //Se comprueba si las balas salen de la pantalla
    if (m_pBody->GetPosition().x < 0 || m_pBody->GetPosition().x > 800 * MPP || m_pBody->GetPosition().y > 600 * MPP) {
        std::cout << "fuera de rango" << std::endl;
        balasAEliminar.insert(this);
    }

    float angle = m_pBody->GetAngle();
    b2Vec2 pos = m_pBody->GetPosition();

    m_Shape->setPosition(pos.x * PPM, pos.y * PPM);
    m_Shape->setRotation((angle * 180) / M_PI);
}

void Bala::Disparar_Parabola(float fuerza, float angulo) {
    m_pBody->ApplyForce(b2Vec2(fuerza * cos(angulo * 3.14 / 180.0f), -fuerza * sin(angulo * 3.14 / 180.0f)), m_pBody->GetWorldCenter(), 1);
}

void Bala::Disparar(float velocidad, float angulo) {
    m_pBody->SetGravityScale(0);
    m_pBody->SetLinearVelocity(b2Vec2(velocidad * cos(angulo * 3.14 / 180.0f), -velocidad * sin(angulo * 3.14 / 180.0f)));
}

sf::RectangleShape Bala::getShape() {
    return *m_Shape;
}

void Bala::Render(sf::RenderWindow *window) {
    window->draw(*m_Shape);
}

Bala::~Bala() {
    m_pBody->GetWorld()->DestroyBody(m_pBody);
    delete m_Shape;
    m_Shape = NULL;
    //Hacer un delete de cada objeto que se ha creado con un New y luego igualarlo a NULL
}





