/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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

    avatars = std::vector<VisibleBody*>(4);
    weaponsIcon = std::vector<VisibleBody*>(4);
    crosses = std::vector<VisibleBody*>(4);
    ammos = std::vector<Texto*>(4);

    positions = std::vector< std::vector<int> >(4);
    for (int i = 0; i < positions.size(); i++) {
        positions[i] = std::vector<int>(2);

    }

    positions[0][0] = 50;
    positions[0][1] = 50; //J1 - Esquina sup izq
    positions[1][0] = w - 50;
    positions[1][1] = 50; //J2 - Esquina sup dcha
    positions[2][0] = 50;
    positions[2][1] = h - 50; //J3 - Esquina inf izq
    positions[3][0] = w - 50;
    positions[3][1] = h - 50; //J4 - Esquina inf dcha

    for (int i = 0; i < 4; i++) {
        crosses[i] = new VisibleBody(positions[i][0], positions[i][1], 100, 100, "./resources/sprites/cross.png", true);
    }
}

Hud* Hud::getInstance() {
    if (instance == NULL) instance = new Hud();
    return (instance);
}

void Hud::update() {
    for (int i = 0; i < players.size(); i++) {
        if (players[i] != NULL) {
            Weapon* weapon = players[i]->getWeapon();
            if (weapon != NULL) {
                string weaponTex = weapon->m_vBody->getTexPath();
                weaponsIcon[i] = new VisibleBody(positions[i][0], positions[i][1], 100, 100, weaponTex, true);
                ammos[i] = new Texto(weapon->ammo, 18, "./resources/fonts/newrotic.ttf", 255, 255, 255);
            }
            std::cout << "acabo update" << std::endl;
        }
    }
}

void Hud::render() {
    std::cout << "entro en render" << std::endl;
    if (!players.empty()) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i] != NULL) {
                std::cout << "entro en bucle render" << std::endl;
                Motorgrafico::getInstance()->draw(avatars[i]->getShape());
                if (!players[i]->isPlayerDead()) {
                    std::cout << "NO ESTA MUERTO" << std::endl;
                    if (weaponsIcon[i] != NULL && ammos[i] != NULL) {
                        Motorgrafico::getInstance()->draw(weaponsIcon[i]->getShape());
                        Motorgrafico::getInstance()->draw(ammos[i]->getDrawable());
                    }

                } else {
                    Motorgrafico::getInstance()->draw(crosses[i]->getShape());
                }
            }
        }
    }
    std::cout << "salgo de render" << std::endl;
}

void Hud::addPlayer(Player* p) {
    std::cout <<"SADASD"<< std::endl;

    players.push_back(p);
    std::cout <<"hiaiiaiai"<< std::endl;
    
    int i = players.size()-1;
    
    avatars.push_back(new VisibleBody(positions[i][0], positions[i][1], 100, 100, players[i]->getTexture(), true));
    
    avatars.back()->setTexRect(0, 0, 300, 200);
    
}

void Hud::deletePlayers() {
}

Hud::~Hud() {
}

