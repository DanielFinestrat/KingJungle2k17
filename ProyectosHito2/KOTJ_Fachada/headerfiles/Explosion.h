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

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "Entidad.h"
#include "../motorfisico/headerfiles/ContactListener.h"
#include "../motorfisico/headerfiles/CuerpoCircular.h"

class Explosion : public Entidad {
public:
    float radioActual;
    float radioMax;
    float incrementoRadio;
   
    sf::Clock deltaClock;
    float difTime;
    sf::Time dt;

    CuerpoCircular *cuerpo;
    sf::CircleShape *m_Shape;
    
    /**
    * Constructor del objeto Explosion
    * @param position Vector2f: posicion de la explosion
    * @param radio float: radio maxio al que alcanzará la explosión
    * @param incremento float: valor con el que aumenta el radio con cada iteración
    * @param inicial float: radio inicial de la explosión
    */
    Explosion(sf::Vector2f position, float radio, float incremento, float inicial);

    /**
    * Actualiza el FixtureBodyDef y CircleShape de la explosión
    */
    void Update();

    /**
    * Renderiza la explosión en la ventana
    * @param window RenderWindow: Ventana de la aplicación
    */
    void Render(sf::RenderWindow *window);

    /**
    * Elimina de memoria las variables de la explosión 
    */
    ~Explosion();
private:

};

#endif /* EXPLOSION_H */

