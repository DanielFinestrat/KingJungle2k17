/* 
 * File:   PlayerJoystick.cpp
 * Author: daniel
 * 
 * Created on 15 de marzo de 2017, 9:45
 */

#include "headerfiles/PlayerJoystick.h"
#include "headerfiles/Partida.h"
#include "headerfiles/Hud.h"
#include <iostream>
#include <vector>

PlayerJoystick::PlayerJoystick(int id) {
    tipo = "Joystick";

    Partida* partida = Partida::getInstance();

    boton b1;
    b1.nombre = "Salto"; //UP
    b1.numBoton = 0;
    b1.pulsado = false;
    misBotones.push_back(b1);

    boton b2;
    b1.nombre = "Disparo"; //R
    b2.numBoton = 2;
    b2.pulsado = false;
    misBotones.push_back(b2);

    boton b3;
    b1.nombre = "Interactuar"; //E
    b3.numBoton = 1;
    b3.pulsado = false;
    misBotones.push_back(b3);

    boton b4;
    b1.nombre = "Burlarse"; //W
    b4.numBoton = 3;
    b4.pulsado = false;
    misBotones.push_back(b4);

    boton b5;
    b1.nombre = "Pausar"; //Q
    b5.numBoton = 7;
    b5.pulsado = false;
    misBotones.push_back(b5);

    estadoEjeX = 0;
    estadoEjeY = 0;

    this->id = id;
    
    player = new Player();
    vector<int> position = partida->mapa->getSpawnPlayer().at(0);
    partida->mapa->spawnPlayer.erase(partida->mapa->spawnPlayer.begin());
    partida->mapa->spawnPlayer.push_back(position);

    player->setPosition(position.at(0), position.at(1));
    player->setColor(partida->worldPlayer.size());

    partida->worldPlayer.push_back(player);
    
    //cout << "He insertado un mando con la id " << this->id << " " << tipo << endl;
}

PlayerJoystick::~PlayerJoystick() {
}

void PlayerJoystick::pressUpdateState(int pressedButton) {
    if (misBotones.at(0).numBoton == pressedButton && !misBotones.at(0).pulsado) {
        misBotones.at(0).pulsado = true;
        player->jump();
    } else if (misBotones.at(1).numBoton == pressedButton && !misBotones.at(1).pulsado) {
        misBotones.at(1).pulsado = true;
        player->shoot();
    } else if (misBotones.at(2).numBoton == pressedButton && !misBotones.at(2).pulsado) {
        misBotones.at(2).pulsado = true;
        player->interact();
    } else if (misBotones.at(3).numBoton == pressedButton && !misBotones.at(3).pulsado) {
        misBotones.at(3).pulsado = true;
        player->mock();
    } else if (misBotones.at(4).numBoton == pressedButton && !misBotones.at(4).pulsado) {
        misBotones.at(4).pulsado = true;
        player->pause();
    }
}

void PlayerJoystick::releaseUpdateState(int releasedButton) {
    if (misBotones.at(0).numBoton == releasedButton) {
        misBotones.at(0).pulsado = false;
        player->updateCanJumpStateState();
    } else if (misBotones.at(1).numBoton == releasedButton) {
        misBotones.at(1).pulsado = false;
    } else if (misBotones.at(2).numBoton == releasedButton) {
        misBotones.at(2).pulsado = false;
    } else if (misBotones.at(3).numBoton == releasedButton) {
        misBotones.at(3).pulsado = false;
    } else if (misBotones.at(4).numBoton == releasedButton) {
        misBotones.at(4).pulsado = false;
    }
}

void PlayerJoystick::checkAxisX(int ejeX) {
    if (ejeX > 10) ejeX = 1;
    else if (ejeX < -10) ejeX = -1;
    else ejeX = 0;

    //1 = derecha
    if (ejeX != estadoEjeX) {
        //cout << "Me muevo en el eje X en la dirección " << ejeX << endl;
        estadoEjeX = ejeX;
        player->changeDirection(estadoEjeX);
    }
}

void PlayerJoystick::checkAxisY(int ejeY) {
    if (ejeY > 10) ejeY = 1;
    else if (ejeY < -10) ejeY = -1;
    else ejeY = 0;

    //1 = agachado
    if (ejeY != estadoEjeY) {
        //cout << "Me muevo en el eje Y en la dirección " << ejeY << endl;
        estadoEjeY = ejeY;
        player->duck(estadoEjeY);
    }
}