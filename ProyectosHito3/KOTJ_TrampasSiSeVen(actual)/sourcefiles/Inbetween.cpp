
/* 
 * File:   Inbetween.cpp
 * Author: danielfinestrat
 * 
 * Created on 16 de mayo de 2017, 19:43
 */

#include "../headerfiles/Player.h"
#include "../motorgrafico/headerfiles/Texto.h"
#include "../headerfiles/Inbetween.h"
#include "../motorgrafico/headerfiles/Motorgrafico.h"

Inbetween::Inbetween(vector<Player*> jugadores) {
    fondo = new Fondo("./resources/fondos/fondomenu.png", true);
    fondo->setPosition(1024 / 2, 600 / 2);

    for (int i = 0; i < jugadores.size(); i++) {
        Player* player = jugadores.at(i);
        puntuacion.push_back(player->getPoints());
        ostringstream stm;
        stm << player->getPoints();
        string puntosString = stm.str();

        VisibleBody* crownBody = new VisibleBody((1024 * (2.0f * i + 1.0f) / 8.0f), 50, 100, 50, Resources::getInstance()->crown, true);
        coronaVB.push_back(crownBody);

        VisibleBody* playerBody = new VisibleBody((1024 * (2.0f * i + 1.0f) / 8.0f), 600 - (puntuacion.at(i) * 500 / 10) - 40, 40, 35, player->getTexture(), true);
        playerBody->setRect(0, 0, 40, 35);        
        if (i == 0) playerBody->setColor(255, 255, 255, 255);
        if (i == 1) playerBody->setColor(255, 255, 000, 255);
        if (i == 2) playerBody->setColor(000, 255, 255, 255);
        if (i == 3) playerBody->setColor(255, 000, 255, 255);       
        playerVB.push_back(playerBody);

        Texto* text = new Texto(puntosString, 25, Resources::getInstance()->myFont, 255, 255, 255);
        text->setPos(playerBody->getPosX() - 35, playerBody->getPosY() - 35 / 2);
        puntuacionText.push_back(text);
    }
}

void Inbetween::render() {
    fondo->Render();
    renderCrowns();
    renderFaces();
    renderPunt();
}

void Inbetween::renderFaces() {
    for (int i = 0; i < playerVB.size(); i++) {
        VisibleBody* toRender = playerVB.at(i);
        Motorgrafico::getInstance()->draw(toRender->getShape());
    }
}

void Inbetween::renderCrowns() {
    for (int i = 0; i < coronaVB.size(); i++) {
        VisibleBody* toRender = coronaVB.at(i);
        Motorgrafico::getInstance()->draw(toRender->getShape());
    }
}

void Inbetween::renderPunt() {
    for (int i = 0; i < puntuacionText.size(); i++) {
        Texto* toRender = puntuacionText.at(i);
        Motorgrafico::getInstance()->draw(toRender->getDrawable());
    }
}

Inbetween::~Inbetween() {
}
