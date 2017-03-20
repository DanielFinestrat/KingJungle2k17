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
        bool inPossession = false;
        
        std::set<Bala*> balasAEliminar;
        std::set<Bala*> listadoBalas;

        sf::Vector2f m_Size;
        b2Body *m_pBody;
        sf::RectangleShape *m_Shape;

        /*Constructor del objeto arma
         * @param b2world world: mundo en el que se encuentran todos los objetos
         * @param vector2f size: tamaño del arma
         * @param vector2f pos: posicion del arma
         * @param float shoot_cadence: Disparos por segundo (n*60) siendo n un numero entre 0 y 1 ---> cadencia de 0.5 = 2 disparo(s)/s
         * @param int BPS: Balas por disparo
         */
        Weapon(b2World *world, sf::Vector2f size, sf::Vector2f pos, float shoot_cadence, int BPS);

        /*Se encarga de actualizar las posiciones de los elementos del arma*/
        void update();
        
        /*Se encarga de actualizar la posicion cuando un jugador tiene el arma
         * @param b2Vec2 pos: vector posicion a la que se movera el arma
         */
        void update(b2Vec2 pos);

        /*Crea balas para añadirlas en el array y seguidamente llamar a la función disparo de Bala
         * @param b2World world: mundo en el que se van a crear las balas
         * @param int orientation: dirección a la que se va a disparar (1 o -1)
         */
        void shoot(b2World *world, int orientation);
        
        /*Funcion que renderiza el arma
         * @param RenderWindow window: Ventana en la que se muestra el programa
         */
        void render(sf::RenderWindow *window);


        ~Weapon();

    private:

};

#endif /* WEAPON_H */

