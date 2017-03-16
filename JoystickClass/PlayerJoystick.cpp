/* 
 * File:   PlayerJoystick.cpp
 * Author: daniel
 * 
 * Created on 15 de marzo de 2017, 9:45
 */
#include "PlayerJoystick.h"

PlayerJoystick::PlayerJoystick(int id, b2World *world) {
    boton b1; b1.nombre = "Salto";          b1.numBoton = 1; b1.pulsado = false; misBotones.push_back(b1);
    boton b2; b1.nombre = "Disparo";        b2.numBoton = 2; b2.pulsado = false; misBotones.push_back(b2);
    boton b3; b1.nombre = "Interactuar";    b3.numBoton = 3; b3.pulsado = false; misBotones.push_back(b3);
    boton b4; b1.nombre = "Agacharse";      b4.numBoton = 4; b4.pulsado = false; misBotones.push_back(b4);
    boton b5; b1.nombre = "Burlarse";       b5.numBoton = 5; b5.pulsado = false; misBotones.push_back(b5);
    boton b6; b1.nombre = "Pausar";         b6.numBoton = 6; b6.pulsado = false; misBotones.push_back(b6);
    
    this->id = id;
    //player = new Player(world);
    
    cout<<"He insertado un mando con la id "<<this->id<<endl;
}

PlayerJoystick::~PlayerJoystick() {
}

void PlayerJoystick::pressUpdateState(int pressedButton){
    if(misBotones.at(0).numBoton == pressedButton && !misBotones.at(0).pulsado){
        misBotones.at(0).pulsado = true;
        cout<<id<<".- He saltado"<<endl;
        //jugador.jump();
    }
    
    else if(misBotones.at(1).numBoton == pressedButton && !misBotones.at(1).pulsado){
        misBotones.at(1).pulsado = true;
        cout<<id<<".- He disparado"<<endl;
        //jugador.shoot();
    }
    
    else if(misBotones.at(2).numBoton == pressedButton && !misBotones.at(2).pulsado){
        misBotones.at(2).pulsado = true;
        cout<<id<<".- He interactuado"<<endl;
        //jugador.interact();
    }
    
    else if(misBotones.at(3).numBoton == pressedButton && !misBotones.at(3).pulsado){
        misBotones.at(3).pulsado = true;
        cout<<id<<".- Me he agachado"<<endl;
        //jugador.duck(true);
    }
    
    else if(misBotones.at(4).numBoton == pressedButton && !misBotones.at(4).pulsado){
        misBotones.at(4).pulsado = true;
        cout<<id<<".- Me he burlado"<<endl;
        //jugador.mock();
    }
    
    else if(misBotones.at(5).numBoton == pressedButton && !misBotones.at(5).pulsado){
        misBotones.at(5).pulsado = true;        
        cout<<id<<".- He pausado"<<endl;
        //jugador.pause(true);
    }
}

void PlayerJoystick::releaseUpdateState(int releasedButton){
    if(misBotones.at(0).numBoton == releasedButton){
        misBotones.at(0).pulsado = false;
    }
    
    else if(misBotones.at(1).numBoton == releasedButton){
        misBotones.at(1).pulsado = false;
    }
    
    else if(misBotones.at(2).numBoton == releasedButton){
        misBotones.at(2).pulsado = false;
    }
    
    else if(misBotones.at(3).numBoton == releasedButton){
        misBotones.at(3).pulsado = false;
        cout<<id<<".- Me he levantado"<<endl;
        //jugador.duck(false);
    }
    
    else if(misBotones.at(4).numBoton == releasedButton){
        misBotones.at(4).pulsado = false;
    }
    
    else if(misBotones.at(5).numBoton == releasedButton){
        misBotones.at(5).pulsado = false;
    }
}

void PlayerJoystick::checkAxisX(int ejeX){
    if(ejeX > 10) ejeX = 1;
    else if(ejeX < -10) ejeX = -1;
    else ejeX = 0;
    
    cout<<"Me muevo en el eje X en la dirección "<<ejeX<<endl;
    //player.move(ejeX);  
}