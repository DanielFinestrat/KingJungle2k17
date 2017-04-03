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

class PlayerKeyboard {
public:
    PlayerKeyboard();
    PlayerKeyboard(b2World*);
    PlayerKeyboard(const PlayerKeyboard& orig);
    virtual ~PlayerKeyboard();

    Player* player;
    int id;
    int ejeX;
    bool invertido;

    void pressUpdateState(int);
    void releaseUpdateState(int);
    void checkAxisX();
    void checkAxisY();

private:

    struct boton {
        string nombre;
        int numBoton;
        bool pulsado;
    };
    vector<boton> misBotones;
    int estadoEjeX;
    int estadoEjeY;
};

#endif /* PLAYERKEYBOARD_H */

