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

void Hud::render() {
    for (int i = 0; i < Partida::getInstance()->worldPlayer.size(); i++) {
            VisibleBody *body = new VisibleBody(positions.at(i).at(0), positions.at(i).at(1), 100, 100, Partida::getInstance()->worldPlayer.at(i)->getTexture(), true);
            body->setTexRect(0, 0, 40, 35);
                  
        if (Partida::getInstance()->worldPlayer.at(i) != NULL) {
            if (i == 1)  {body->setColor(255, 70, 70, 255); body->setScale(-1,1);}
            if (i == 2)  body->setColor(70, 255, 70, 255);
            if (i == 3)  {body->setColor(70, 70, 255, 255); body->setScale(-1,1);}
            Motorgrafico::getInstance()->draw(body->getShape());
            
            if (!Partida::getInstance()->worldPlayer.at(i)->isPlayerDead()) {

                Weapon * weapon = Partida::getInstance()->worldPlayer.at(i)->getWeapon();
                if (weapon != NULL) {
                    VisibleBody * bodyP  = weapon->getVBody();
                    VisibleBody body = *bodyP;
                   
                    if (i == 0) { body.setPos(100, 100); body.setScale(1,1);}
                    if (i == 1) { body.setPos(positions.at(i).at(0)-50, 100); body.setScale(-1,1); }
                    if (i == 2) { body.setPos(100, positions.at(i).at(1)-30); body.setScale(1,1);}
                    if (i == 3) { body.setPos(positions.at(i).at(0)-50, positions.at(i).at(1)-30); body.setScale(-1,1);}
                    Motorgrafico::getInstance()->draw(body.getShape());
                    
                    if (weapon->getAmmo() >= 0 ) {
                        Texto * ammo =  new Texto(weapon->getAmmo(), 25, Resources::getInstance()->menuFont, 255, 255, 255);
                        if (i == 0) ammo->setPos(110, 90);
                        if (i == 1) ammo->setPos(positions.at(i).at(0)-70, 90);
                        if (i == 2) ammo->setPos(110, positions.at(i).at(1)-60);
                        if (i == 3) ammo->setPos(positions.at(i).at(0)-70, positions.at(i).at(1)-60);
                        Motorgrafico::getInstance()->draw(ammo->getDrawable());
                    }
                }
                
                if(Partida::getInstance()->rondas.at(Partida::getInstance()->rondaActual).modoJuego == 1) {
                    Texto * coins =  new Texto(Partida::getInstance()->worldPlayer.at(i)->getMonedero(), 25, Resources::getInstance()->menuFont, 195, 195, 27);
                    if (i == 0) coins->setPos(20, 100);
                    if (i == 1) coins->setPos(positions.at(i).at(0), 100);
                    if (i == 2) coins->setPos(20, positions.at(i).at(1)-70);
                    if (i == 3) coins->setPos(positions.at(i).at(0), positions.at(i).at(1)-70);
                    Motorgrafico::getInstance()->draw(coins->getDrawable());
                    
                }
            }
            else Motorgrafico::getInstance()->draw(crosses.at(i)->getShape());
        }
    }
}

Hud::~Hud() {
}

