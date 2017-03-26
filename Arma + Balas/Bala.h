/* 
 * File:   Bala.h
 * Author: angel
 *
 * Created on 16 de marzo de 2017, 20:43
 */

#ifndef BALA_H
#define BALA_H

#include <iostream>
#include <set>
#include <vector>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"


class Bala {
public:
    sf::Vector2f m_Size;
    b2Body *m_pBody;
    sf::RectangleShape *m_Shape;

    /**
     * Constructor del objeto Bala
     * @param mundo b2World*: mundo en el que estan todos los objetos
     * @param size Vector2f: tamaño de la bala
     * @param pos Vector2f: posicion de la bala
     */
    Bala(b2World *world, sf::Vector2f size, sf::Vector2f pos);

    /**
     * Actualiza el RectangleShape del objeto
     */
    void Update_Shape(std::set<Bala*> &balasAEliminar);

    /**
     * Le añade una fuerza a la bala en la direccion selecciona afectandole la gravedad
     * @param fuerza float: fuerza a la que se dispara
     * @param angulo float: direccion del movimiento (grados)
     */
    void Disparar_Parabola(float fuerza, float angulo);

    /**
     * Le aplica una velocidad constane a la bala en la direccion seleccionada
     * @param velocidad float: velocidad de la bala
     * @param angulo float: direccion del movimiento (grados)
     */
    void Disparar(float velocidad, float angulo);

    sf::RectangleShape getShape();

    void Render(sf::RenderWindow *window);

    ~Bala();

};

#endif /* BALA_H */

