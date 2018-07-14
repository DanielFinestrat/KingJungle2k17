
/* 
 * File:   PlayerJoystick.h
 * Author: daniel
 *
 * Created on 15 de marzo de 2017, 9:45
 */

#ifndef PLAYERJOYSTICK_H
#define PLAYERJOYSTICK_H

#include "Player.h"
#include "Controlador.h"

using namespace std;

class PlayerJoystick : public Controlador {
public:

    PlayerJoystick(int id);
    virtual ~PlayerJoystick();

    void pressUpdateState(int botonPulsado);
    void releaseUpdateState(int botonSoltado);
    void checkAxisX(int ejeX);
    void checkAxisY(int ejeY);

private:

};

#endif
