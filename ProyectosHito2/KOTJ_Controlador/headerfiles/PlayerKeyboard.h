/* 
 * File:   PlayerKeyboard.h
 * Author: amygwyllion
 *
 * Created on 29 de marzo de 2017, 11:20
 */

#ifndef PLAYERKEYBOARD_H
#define PLAYERKEYBOARD_H

#include <iostream>
#include <vector>
#include "../Box2D/Box2D.h"
#include "Player.h"
#include "Controlador.h"

class PlayerKeyboard : public Controlador{
public:
    
    PlayerKeyboard(b2World *world);
    virtual ~PlayerKeyboard();

    int id;
    int ejeX;
    bool invertido;

    void pressUpdateState(int botonPulsado);
    void releaseUpdateState(int botonPulsado);
    void checkAxisX();
    void checkAxisY();

};

#endif /* PLAYERKEYBOARD_H */

