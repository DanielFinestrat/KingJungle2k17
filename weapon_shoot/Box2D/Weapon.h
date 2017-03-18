/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   weapon.h
 * Author: pedro
 *
 * Created on 16 de marzo de 2017, 20:24
 */


#include "Bala.h"

#ifndef WEAPON_H
#define WEAPON_H


class Weapon {
    public:
        float shootCadence; //Shots per second
        int BPS; //Bullets per shot
        
        std::set<Bala*> balasAEliminar;
        std::set<Bala*> listadoBalas;

        sf::Vector2f m_Size;
        b2Body *m_pBody;
        sf::RectangleShape *m_Shape;

        /*Constructor del objeto arma
         * @param b2world world: mundo en el que se encuentran todos los objetos
         * @param vector2f size: tamaño del arma
         * @param vector2f pos: posicion del arma
         * @param float shoot_cadence: Disparos por segundo (entre 0 y 1)
         * @param int BPS: Balas por disparo
         */
        Weapon(b2World *world, sf::Vector2f size, sf::Vector2f pos, float shoot_cadence, int BPS);

        /*Se encarga de actualizar las posiciones de los elementos del arma*/
        void update();

        /*Crea balas para añadirlas en el array y seguidamente llamar a la función disparo de Bala
         * @param b2World world: mundo en el que se van a crear las balas
         */
        void shoot(b2World *world);
        
        /*Funcion que renderiza el arma
         * @param RenderWindow window: Ventana en la que se muestra el programa
         */
        void render(sf::RenderWindow *window);


        ~Weapon();

    private:

};

#endif /* WEAPON_H */

