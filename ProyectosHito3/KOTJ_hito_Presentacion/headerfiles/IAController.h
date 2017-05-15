
/* 
 * File:   IAController.h
 * Author: angel
 *
 * Created on 25 de abril de 2017, 14:12
 */

#ifndef IACONTROLLER_H
#define IACONTROLLER_H

#include <iostream>
#include "../Box2D/Box2D.h"
#include "Player.h"
#include "Controlador.h"

class IAController : public Controlador {
public:
    
    string estado;
    int layerSubir = 3;
    int layerMisma;
    int layerBajar = 1;
    //buscarArma - MatarJugador - Huir 
    
    IAController();
    virtual ~IAController();
    
    void pressUpdateState(int botonPulsado);
    void releaseUpdateState(int botonSoltado);
    void checkAxisX(int ejeX);
    void checkAxisY(int ejeY);
    
    bool disparar(float dist, float PosX);
    void update();
    int readTile(int layer);
    void moveTo(float PosX, float PosY, float dist, Controlador* seguir);
    void interact();
    vector<float> buscarArma();
    vector<float> buscarHuida();
    vector<float> buscarMatar(Controlador **seguir);

};

#endif /* IACONTROLLER_H */
