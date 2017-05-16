/* 
 * File:   Hud.cpp
 * Author: pedro
 * 
 * Created on 30 de abril de 2017, 13:35
 */

#include "../headerfiles/Hud.h"
#include "../motorgrafico/headerfiles/Motorgrafico.h"

static Hud* instance;

Hud::Hud() {
    int w = 1024;
    int h = 600;

    //J1 - Esquina sup izq
    vector<int> vector1;
    vector1.push_back(50);
    vector1.push_back(50);
    positions.push_back(vector1);

    //J2 - Esquina sup dcha
    vector<int> vector2;
    vector2.push_back(w - 50);
    vector2.push_back(50);
    positions.push_back(vector2);

    //J3 - Esquina inf izq
    vector<int> vector3;
    vector3.push_back(50);
    vector3.push_back(h - 50);
    positions.push_back(vector3);

    //J4 - Esquina inf dcha
    vector<int> vector4;
    vector4.push_back(w - 50);
    vector4.push_back(h - 50);
    positions.push_back(vector4);

    for (int i = 0; i < 4; i++) {
        crosses.push_back(new VisibleBody(positions[i][0], positions[i][1], 100, 100, Resources::getInstance()->cross, true));
    }
}

Hud* Hud::getInstance() {
    if (instance == NULL) instance = new Hud();
    return (instance);
}

void Hud::update() {
    for (int i = 0; i < players.size(); i++) {
        if (players.at(i) != NULL) {
            Weapon* weapon = players.at(i)->getWeapon();
            if (weapon != NULL) {
                string weaponTex = weapon->m_vBody->getTexPath();
                weaponsIcon.push_back(new VisibleBody(positions[i][0], positions[i][1], 100, 100, weaponTex, true));
                ammos.push_back(new Texto(weapon->ammo, 18, Resources::getInstance()->menuFont, 255, 255, 255));
            }
        }
    }
}

void Hud::render() {
    for (int i = 0; i < players.size(); i++) {
        if (players.at(i) != NULL) {
            Motorgrafico::getInstance()->draw(avatars.at(i)->getShape());
            if (!players.at(i)->isPlayerDead()) {
                if (weaponsIcon.size() > i && ammos.size() > i) {
                    Motorgrafico::getInstance()->draw(weaponsIcon.at(i)->getShape());
                    Motorgrafico::getInstance()->draw(ammos.at(i)->getDrawable());
                }
            }
            else Motorgrafico::getInstance()->draw(crosses.at(i)->getShape());
        }
    }
}

void Hud::addPlayer(Player* p) {
    players.push_back(p);
    int i = players.size() - 1;

    VisibleBody *body = new VisibleBody(positions[i][0], positions[i][1], 100, 100, p->getTexture(), true);
    body->setTexRect(0, 0, 300, 200);
    avatars.push_back(body);
}

void Hud::deletePlayers() {
}

Hud::~Hud() {
}

