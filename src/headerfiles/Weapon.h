
/* 
 * File:   weapon.h
 * Author: pedro
 *
 * Created on 16 de marzo de 2017, 20:24
 */

#ifndef WEAPON_H
#define WEAPON_H

#include "Bala.h"
#include "Entidad.h"
#include "../motorgrafico/headerfiles/VisibleBody.h"
#include "../motorfisico/headerfiles/Cuerpo.h"
#include "../motorgrafico/headerfiles/InnerClock.h"
#include "../motorgrafico/headerfiles/resources.h"

using namespace std;

class Weapon : public Entidad {
public:
    int BPS; //Bullets per shot
    int ammo; //Municion actual del arma
    int dir; //Direccion a la que apunta el arma
    int recoil;
    int rango;
    float shootCadence; //Shots per second
    bool parabola;
    bool explosivo;

    bool balasVisibles;

    bool inPossession;
    bool used;

    bool atackPressed; //Activa la animacion de ataque de la espada		
    InnerClock animationClock;
    float animtime;

    //Variables para controlar la cadencia de disparo
    InnerClock deltaClock;
    float difTime;
    time_t lastShot;

    std::set<Bala*> balasAEliminar;
    std::set<Bala*> listadoBalas;

    float m_sizex;
    float m_sizey;
    Cuerpo *cuerpo;
    VisibleBody *m_vBody;

    /**
     * Constructor del objeto arma
     * @param b2world world: mundo en el que se encuentran todos los objetos
     * @param vector2f size: tamaño del arma
     * @param vector2f pos: posicion del arma
     * @param float shoot_cadence: Disparos por segundo 
     * @param int BPS: Balas por disparo
     * @param int ammo: Municion del arma
     */
    Weapon(float sizex, float sizey, float posx, float posy, float shoot_cadence, int BPS, int ammo, int recoil_, int rango, bool parabola, bool explosivo);

    ~Weapon();

    //Se encarga de actualizar las posiciones de los elementos del arma
    void update();

    /**
     * Se encarga de actualizar la posicion cuando un jugador tiene el arma
     * @param float posX: Posicion en X del arma
     * @param float posY: Posicion en Y del arma
     */
    void update(float posX, float posY);

    /**
     * Crea balas para añadirlas en el array y seguidamente llamar a la función disparo de Bala
     * @param b2World world: mundo en el que se van a crear las balas
     */
    int shoot();

    /**
     * Funcion para editar la posesion del arma
     * @param bool var: Puede ser true o false
     */
    void setPossession(bool var);

    //Funcion que lanza el arma en posesion de un personaje
    void throwWeapon(float playerVel);

    /**
     * Funcion para modificar la direccion a la que apunta el arma
     * @param int i: Puede ser 1 o -1
     */
    void setDir(int i);
    /*
     * Funcion que devuelve un puntero al VisibleBody del arma
     */
    VisibleBody* getVBody();

    /*
     * Funcion que devuelve la municion actual del arma
     */
    int getAmmo();


    /**
     * Funcion que mueve el cuerpo del arma
     * @param x: posicion en x
     * @param y: posicion en y
     */
    void moveWeapon(float x, float y);

    /**
     * Comprueba si se puede borrar el arma (0 balas)
     */

    void checkIfDelete();

    void doDelete();

    float getRango();

    void Contact(void* punt, string tipo);
};

#endif /* WEAPON_H */
