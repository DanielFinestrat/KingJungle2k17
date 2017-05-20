
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

Inbetween::Inbetween(vector<Player*> jugadores, int maxPoints) {
    fondo = new Fondo("./resources/fondos/fondomenu.png", false);
    fondo->setPosition(1024 / 2, 600 / 2);

    for (int i = 0; i < jugadores.size(); i++) {
        Player* player = jugadores.at(i);
        puntuacion.push_back(player->getPoints());
        ostringstream stm;
        stm << player->getPoints();
        string puntosString = stm.str();

        VisibleBody* crownBody = new VisibleBody((1024 * (2.0f * i + 1.0f) / 8.0f), 50, 150, 75, Resources::getInstance()->crown, true);
        coronaVB.push_back(crownBody);

        VisibleBody* playerBody = new VisibleBody((1024 * (2.0f * i + 1.0f) / 8.0f), 600 - (puntuacion.at(i) * 500 / maxPoints) - 60, 60, 55, player->getTexture(), true);
        playerBody->setRect(0, 0, 40, 35);
        if (i == 0) playerBody->setColor(255, 255, 255, 255);
        if (i == 1) playerBody->setColor(255, 255, 000, 255);
        if (i == 2) playerBody->setColor(000, 255, 255, 255);
        if (i == 3) playerBody->setColor(255, 000, 255, 255);
        playerVB.push_back(playerBody);

        Texto* text = new Texto(puntosString, 35, Resources::getInstance()->myFont, 255, 255, 255);
        text->setPos(playerBody->getPosX() - 55, playerBody->getPosY() - 35 / 2);
        puntuacionText.push_back(text);
    }

    isRendered = false;
}

void Inbetween::render() {
    if (!isRendered) {
        isRendered = true;
        Motorgrafico::getInstance()->setHudCameraView();
        fondo->Render();
        renderCrowns();
        renderFaces();
        renderPunt();
        Motorgrafico::getInstance()->displayWindow();
    }
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
