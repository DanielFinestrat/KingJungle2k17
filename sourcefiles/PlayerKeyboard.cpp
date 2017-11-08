/* 
 * File:   PlayerKeyboard.cpp
 * Author: amygwyllion
 * 
 * Created on 29 de marzo de 2017, 11:20
 */

#include "../headerfiles/PlayerKeyboard.h"
#include "../headerfiles/Partida.h"
#include "../headerfiles/Hud.h"

PlayerKeyboard::PlayerKeyboard() {
    tipo = "Keyboard";
	
    Partida* partida = Partida::getInstance();
	
    boton b1;
    b1.nombre = "Salto";
    b1.numBoton = 73;
    b1.pulsado = false;
    misBotones.push_back(b1);
    
    boton b2;
    b2.nombre = "Disparo";
    b2.numBoton = 17;
    b2.pulsado = false;
    misBotones.push_back(b2);
    
    boton b3;
    b3.nombre = "Interactuar";
    b3.numBoton = 4;
    b3.pulsado = false;
    misBotones.push_back(b3);
    
    boton b4;
    b4.nombre = "Burlarse";
    b4.numBoton = 22;
    b4.pulsado = false;
    misBotones.push_back(b4);
    
    boton b5;
    b5.nombre = "Pausar";
    b5.numBoton = 16;
    b5.pulsado = false;
    misBotones.push_back(b5);
    
    boton b6;
    b6.nombre = "Izquierda";
    b6.numBoton = 71;
    b6.pulsado = false;
    misBotones.push_back(b6);
    
    boton b7;
    b7.nombre = "Derecha";
    b7.numBoton = 72;
    b7.pulsado = false;
    misBotones.push_back(b7);
    
    boton b8;
    b8.nombre = "Agacharse";
    b8.numBoton = 74;
    b8.pulsado = false;
    misBotones.push_back(b8);

    estadoEjeX = 0;
    estadoEjeY = 0;
    ejeX = 0;
    invertido = false;
     
    id = partida->worldPlayer.size();
  
    player = new Player();
    vector<int> position = partida->mapa->getSpawnPlayer().at(0);
    partida->mapa->spawnPlayer.erase(partida->mapa->spawnPlayer.begin());
    partida->mapa->spawnPlayer.push_back(position);

    player->setPosition(position.at(0), position.at(1));
    player->setColor(id);
    partida->worldPlayer.push_back(player);

    //cout << "Se ha unido el jugador con teclado con id: " << this->id << " " << tipo << endl;
}

PlayerKeyboard::~PlayerKeyboard() {
}

void PlayerKeyboard::pressUpdateState(int keycode){
    if (misBotones.at(0).numBoton == keycode && !misBotones.at(0).pulsado) {
        misBotones.at(0).pulsado = true;
        player->jump();
    }
    else if (misBotones.at(1).numBoton == keycode && !misBotones.at(1).pulsado) {
        misBotones.at(1).pulsado = true;
        player->shoot();
    }
    else if (misBotones.at(2).numBoton == keycode && !misBotones.at(2).pulsado) {
        misBotones.at(2).pulsado = true;
        player->interact();
    }
    else if (misBotones.at(3).numBoton == keycode && !misBotones.at(3).pulsado) {
        misBotones.at(3).pulsado = true;
        player->mock();
    }
    else if (misBotones.at(4).numBoton == keycode && !misBotones.at(4).pulsado) {
        misBotones.at(4).pulsado = true;
        player->pause();
    }
    else if(misBotones.at(5).numBoton == keycode && !misBotones.at(5).pulsado){
        misBotones.at(5).pulsado = true;
    }
    else if(misBotones.at(6).numBoton == keycode && !misBotones.at(6).pulsado){
        misBotones.at(6).pulsado = true;
    }
    else if(misBotones.at(7).numBoton == keycode && !misBotones.at(7).pulsado){
        misBotones.at(7).pulsado = true;
    }
    
    checkAxisX();
    checkAxisY();
}

void PlayerKeyboard::releaseUpdateState(int keycode){
    if (misBotones.at(0).numBoton == keycode) {
        misBotones.at(0).pulsado = false;
        player->updateCanJumpStateState();
    }
    else if (misBotones.at(1).numBoton == keycode) {
        misBotones.at(1).pulsado = false;
    }
    else if (misBotones.at(2).numBoton == keycode) {
        misBotones.at(2).pulsado = false;
    }
    else if (misBotones.at(3).numBoton == keycode) {
        misBotones.at(3).pulsado = false;
    }
    else if (misBotones.at(4).numBoton == keycode) {
        misBotones.at(4).pulsado = false;
    }
    else if (misBotones.at(5).numBoton == keycode) {
        misBotones.at(5).pulsado = false;
    }
    else if (misBotones.at(6).numBoton == keycode) {
        misBotones.at(6).pulsado = false;
    }
    else if (misBotones.at(7).numBoton == keycode) {
        misBotones.at(7).pulsado = false;
    }
    
    checkAxisX();
    checkAxisY();
    
}

void PlayerKeyboard::checkAxisX() {
    if(misBotones.at(5).pulsado == true && misBotones.at(6).pulsado == true){
        if(invertido==false){
            ejeX=-estadoEjeX;
            invertido = true;
        }
    }
    else if(misBotones.at(5).pulsado == true){
        ejeX = -1;
        invertido = false;
    }
    else if(misBotones.at(6).pulsado == true){
        ejeX = 1;
        invertido = false;
    }
    else{
        ejeX = 0;
    }

    //1 = derecha
    if (ejeX != estadoEjeX) {
        //cout << "Me muevo en el eje X en la dirección " << ejeX << endl;
        estadoEjeX = ejeX;
        player->changeDirection(estadoEjeX);
    }
}

void PlayerKeyboard::checkAxisY() {
    int ejeY;
    ejeY = misBotones.at(7).pulsado == true ? 1 : 0;

    //1 = agachado
    if (ejeY != estadoEjeY) {
        //cout << "Me muevo en el eje Y en la dirección " << ejeY << endl;
        estadoEjeY = ejeY;
        player->duck(estadoEjeY);
    }
}

