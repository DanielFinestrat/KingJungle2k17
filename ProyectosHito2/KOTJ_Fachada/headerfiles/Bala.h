/* 
 * File:   Bala.h
 * Author: angel
 *
 * Created on 16 de marzo de 2017, 20:43
 */

#ifndef BALA_H
#define BALA_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <set>
#include <vector>
#include "Entidad.h"
#include "../motorfisico/headerfiles/Cuerpo.h"

class Bala : public Entidad {
public:
    sf::Vector2f m_Size;
    bool explosion;

    Cuerpo *cuerpo;
    sf::RectangleShape *m_Shape;

    /**
     * Constructor del objeto Bala
     * @param mundo b2World*: mundo en el que estan todos los objetos
     * @param size Vector2f: tamaño de la bala
     * @param position Vector2f: posicion inicial de la bala
     * @param explo bool: activar la explosion al eliminar la bala
     */
    Bala(sf::Vector2f size, sf::Vector2f position, bool explo);

    /**
     * Actualiza el RectangleShape del objeto
     */
    void Update_Shape();

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

    /**
     * Renderiza la bala en la ventana
     * @param window RenderWindow: Ventana de la aplicación
     */
    void Render(sf::RenderWindow *window);

    /**
     * Elimina de memoria las variables de la bala
     */
    ~Bala();
};

#endif /* BALA_H */

