
/* 
 * File:   Controlador.h
 * Author: anm39
 *
 * Created on 5 de abril de 2017, 9:53
 */

#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

class Controlador {
public:

    Player* player;
    int id;
    string tipo;

    Controlador();
    virtual ~Controlador();

    virtual void pressUpdateState(int botonPulsado);
    virtual void releaseUpdateState(int botonSoltado);
    virtual void checkAxisX(int ejeX);
    virtual void checkAxisY(int ejeY);

protected:

    struct boton {
        string nombre;
        int numBoton;
        bool pulsado;
    };
    vector<boton> misBotones;
    int estadoEjeX;
    int estadoEjeY;


};

#endif /* CONTROLADOR_H */

