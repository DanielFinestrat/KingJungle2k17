/* 
 * File:   PlayerJoystick.h
 * Author: daniel
 *
 * Created on 15 de marzo de 2017, 9:45
 */

#ifndef PLAYERJOYSTICK_H
#define PLAYERJOYSTICK_H

#include <iostream>
#include <vector>
#include "Box2D/Box2D.h"
//#include "Player.h"

using namespace std;

class PlayerJoystick {
public: 
    struct boton{
        string nombre;
        int numBoton;
        bool pulsado;
    };
    vector<boton> misBotones;
    int estadoEjeX;
    int estadoEjeY;
    //Player player;
    int id;
    
    PlayerJoystick(int id, b2World *world);
    virtual ~PlayerJoystick();
    
    void pressUpdateState(int botonPulsado);
    void releaseUpdateState(int botonSoltado);
    void checkAxisX(int ejeX);
    void checkAxisY(int ejeY);

private:

};

#endif

