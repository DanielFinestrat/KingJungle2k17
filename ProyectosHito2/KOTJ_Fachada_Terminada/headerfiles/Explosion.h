
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Explosion.h
 * Author: angel
 *
 * Created on 2 de abril de 2017, 23:50
 */

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <stdio.h>
#include <iostream>
#include "Entidad.h"
#include "../motorfisico/headerfiles/ContactListener.h"
#include "../motorfisico/headerfiles/CuerpoCircular.h"
#include "../motorgrafico/headerfiles/VisibleFigure.h"
#include "../motorgrafico/headerfiles/InnerClock.h"

class Explosion : public Entidad {
public:
    float radioActual;
    float radioMax;
    float incrementoRadio;
   
    InnerClock deltaClock;
    float difTime;

    CuerpoCircular *cuerpo;
    VisibleFigure *figure;
    
    /**
    * Constructor del objeto Explosion
    * @param posx float: posicion de la explosion en el eje x
    * @param posy float: posicion de la explosion en el eje y
    * @param radio float: radio maxio al que alcanzará la explosión
    * @param incremento float: valor con el que aumenta el radio con cada iteración
    * @param inicial float: radio inicial de la explosión
    */
    Explosion(float posx, float posy, float radio, float incremento, float inicial);

    /**
    * Actualiza el CuerpoCircular y VisibleFigure de la explosión
    */
    void Update();

    /**
    * Elimina de memoria las variables de la explosión 
    */
    ~Explosion();
private:

};

#endif /* EXPLOSION_H */

