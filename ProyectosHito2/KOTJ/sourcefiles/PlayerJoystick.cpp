/* 
 * File:   PlayerJoystick.cpp
 * Author: daniel
 * 
 * Created on 15 de marzo de 2017, 9:45
 */
#include "../headerfiles/PlayerJoystick.h"
#include "../headerfiles/Partida.h"

PlayerJoystick::PlayerJoystick(int id, b2World *world) {
    boton b1;
    b1.nombre = "Salto";
    b1.numBoton = 0;
    b1.pulsado = false;
    misBotones.push_back(b1);
    
    boton b2;
    b1.nombre = "Disparo";
    b2.numBoton = 2;
    b2.pulsado = false;
    misBotones.push_back(b2);
    
    boton b3;
    b1.nombre = "Interactuar";
    b3.numBoton = 1;
    b3.pulsado = false;
    misBotones.push_back(b3);
    
    boton b4;
    b1.nombre = "Burlarse";
    b4.numBoton = 3;
    b4.pulsado = false;
    misBotones.push_back(b4);
    
    boton b5;
    b1.nombre = "Pausar";
    b5.numBoton = 7;
    b5.pulsado = false;
    misBotones.push_back(b5);

    estadoEjeX = 0;
    estadoEjeY = 0;

    this->id = id;
    player = new Player(*world);
    player->setPosition((id+1) * screenWidth/5, screenHeight-100);
    player->setColor(id);

    cout << "He insertado un mando con la id " << this->id << endl;
}

PlayerJoystick::~PlayerJoystick() {
}

void PlayerJoystick::pressUpdateState(int pressedButton) {
    if (misBotones.at(0).numBoton == pressedButton && !misBotones.at(0).pulsado) {
        misBotones.at(0).pulsado = true;
        cout << id << ".- He saltado" << endl;
        player->jump();
    }
    else if (misBotones.at(1).numBoton == pressedButton && !misBotones.at(1).pulsado) {
        misBotones.at(1).pulsado = true;
        cout << id << ".- He disparado" << endl;
        player->shoot();
    }
    else if (misBotones.at(2).numBoton == pressedButton && !misBotones.at(2).pulsado) {
        misBotones.at(2).pulsado = true;
        cout << id << ".- He interactuado" << endl;
        player->interact();
    }
    else if (misBotones.at(3).numBoton == pressedButton && !misBotones.at(3).pulsado) {
        misBotones.at(3).pulsado = true;
        cout << id << ".- Me he burlado" << endl;
        player->mock();
    }
    else if (misBotones.at(4).numBoton == pressedButton && !misBotones.at(4).pulsado) {
        misBotones.at(4).pulsado = true;
        cout << id << ".- He pausado" << endl;
        player->pause(true);
    }
}

void PlayerJoystick::releaseUpdateState(int releasedButton) {
    if (misBotones.at(0).numBoton == releasedButton) {
        misBotones.at(0).pulsado = false;
        player->updateCanJumpStateState();
    }
    else if (misBotones.at(1).numBoton == releasedButton) {
        misBotones.at(1).pulsado = false;
    }
    else if (misBotones.at(2).numBoton == releasedButton) {
        misBotones.at(2).pulsado = false;
    }
    else if (misBotones.at(3).numBoton == releasedButton) {
        misBotones.at(3).pulsado = false;
    }
    else if (misBotones.at(4).numBoton == releasedButton) {
        misBotones.at(4).pulsado = false;
    }
}

void PlayerJoystick::checkAxisX(int ejeX) {
    if (ejeX > 10) ejeX = 1;
    else if (ejeX < -10) ejeX = -1;
    else ejeX = 0;

    //1 = derecha
    if (ejeX != estadoEjeX) {
        cout << "Me muevo en el eje X en la dirección " << ejeX << endl;
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
        cout << "Me muevo en el eje Y en la dirección " << ejeY << endl;
        estadoEjeY = ejeY;
        player->duck(estadoEjeY);
    }
}