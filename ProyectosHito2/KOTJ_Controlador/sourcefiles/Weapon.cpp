/* 
 * File:   weapon.cpp
 * Author: pedro
 * 
 * Created on 16 de marzo de 2017, 20:24
 */

#include "../headerfiles/Weapon.h"
#include "../headerfiles/Partida.h"

Weapon::Weapon(b2World *world, sf::Vector2f size, sf::Vector2f pos, float shoot_cad, int Bps, int amm, int recoil_, bool parabola, bool explosivo) {

    tag = "Weapon";

    shootCadence = shoot_cad;
    BPS = Bps;
    m_Size = size;
    ammo = amm;
    recoil = recoil_;

    this->parabola = parabola;
    this->explosivo = explosivo;
    
    inPossession = false;
    dir = 1;
    difTime = (1 / shootCadence) * 1000;
    
    b2BodyDef weaponBodyDef;
    weaponBodyDef.userData = this;
    weaponBodyDef.type = b2_dynamicBody;
    weaponBodyDef.position.Set(pos.x*MPP, pos.y * MPP);
    m_pBody = world->CreateBody(&weaponBodyDef);

    b2PolygonShape weaponBox;
    weaponBox.SetAsBox(size.x / 2 * MPP, size.y / 2 * MPP);

    b2FixtureDef weaponFixtureDef;
    weaponFixtureDef.shape = &weaponBox;
    weaponFixtureDef.friction = 0.5f;
    weaponFixtureDef.restitution = 0.3f;
    weaponFixtureDef.density = 1.0f;
    weaponFixtureDef.filter.categoryBits = CATEGORY_GUN;
    weaponFixtureDef.filter.maskBits = MASK_GUN;

    m_pBody->CreateFixture(&weaponFixtureDef);

    m_Shape = new sf::RectangleShape(size);
    m_Shape->setOrigin(Vector2f(size.x / 2, size.y / 2));
    m_Shape->setPosition(Vector2f(m_pBody->GetPosition().x, m_pBody->GetPosition().y));
    m_Shape->setFillColor(Color::White);

    //Creamos la textura y el sprite
    if (!weapon_texture.loadFromFile("resources/sprites/revolver.png")) {
        cerr << "Error cargando la imagen revolver.png" << endl;
    }
    weapon_texture.setSmooth(true);
    m_Shape->setTexture(&weapon_texture);

}

void Weapon::update() {
    b2Vec2 pos = m_pBody->GetPosition();
    m_pBody->SetTransform(pos, 0);
    m_Shape->setOrigin(m_Size.x / 2, m_Size.y / 2);
    m_Shape->setPosition(pos.x * PPM, pos.y * PPM);
    m_Shape->setRotation((m_pBody->GetAngle()*180) / M_PI);
}

void Weapon::update(b2Vec2 pos) {
    m_pBody->SetTransform(pos, 0);
    m_Shape->setOrigin(m_Size.x / 2, m_Size.y / 2);
    m_Shape->setPosition(pos.x * PPM, pos.y * PPM);
    m_Shape->setRotation((m_pBody->GetAngle()*180) / M_PI);
}

int Weapon::shoot() {
    if (ammo > 0) {
        dt = deltaClock.restart();
        difTime += dt.asSeconds();

        if (difTime >= shootCadence) {
            difTime = 0.0;
            ammo--;
            Partida *partida = Partida::getInstance();
            // +50 habria que cambiarlo por el size del personaje
            Bala* nuevaBala = new Bala(partida->world, Vector2f(10, 4), Vector2f(m_pBody->GetPosition().x * PPM + 50 * dir, m_pBody->GetPosition().y * PPM), explosivo);
            
            if(!parabola) nuevaBala->Disparar(5 * -dir, 180);
            else nuevaBala->Disparar_Parabola(-dir, 160);
                
            partida->worldBullets.insert(nuevaBala);
            return recoil;
        }
    }
    return 0;
}

void Weapon::render(sf::RenderWindow *window) {
    window->draw(*m_Shape);
}

void Weapon::setPossession(bool var) {
    inPossession = var;
}

void Weapon::throwWeapon(float playerVel) {

    inPossession = false;
    m_pBody->SetActive(true);

    //Lanzarla para arriba si está quieto o anda despacio
    if (fabs(playerVel) < 0.3) m_pBody->ApplyForceToCenter(b2Vec2(0, -30), 1);
        //Lanzarla hacia donde mire la pistola
    else m_pBody->ApplyForceToCenter(b2Vec2(dir * 30 * fabs(playerVel), -20), 1);

}

void Weapon::setDir(int i) {
    dir = i;
    m_Shape->scale(-1, 1);
}

Weapon::~Weapon() {
}




