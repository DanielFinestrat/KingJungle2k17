
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

using namespace std;

class Weapon : public Entidad {
public:
    float shootCadence; //Shots per second
    int BPS; //Bullets per shot
    bool inPossession; //Indica si el arma esta en posesion de un personaje
    int ammo; //Municion actual del arma
    int dir; //Direccion a la que apunta el arma
    int recoil;
    
    bool parabola;
    bool explosivo;

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

    /*Constructor del objeto arma
     * @param b2world world: mundo en el que se encuentran todos los objetos
     * @param vector2f size: tamaño del arma
     * @param vector2f pos: posicion del arma
     * @param float shoot_cadence: Disparos por segundo 
     * @param int BPS: Balas por disparo
     * @param int ammo: Municion del arma
     */
    Weapon(float sizex, float sizey, float posx, float posy, float shoot_cadence, int BPS, int ammo, int recoil_, bool parabola, bool explosivo);
    ~Weapon();

    /*Se encarga de actualizar las posiciones de los elementos del arma*/
    void update();

    /*Se encarga de actualizar la posicion cuando un jugador tiene el arma
     * @param float posX: Posicion en X del arma
     * @param float posY: Posicion en Y del arma
     */
    void update(float posX, float posY);

    /*Crea balas para añadirlas en el array y seguidamente llamar a la función disparo de Bala
     * @param b2World world: mundo en el que se van a crear las balas
     */
    int shoot();
    
    /*Funcion para editar la posesion del arma
     * @param bool var: Puede ser true o false
     */
    void setPossession(bool var);

    /*Funcion que lanza el arma en posesion de un personaje
     */
    void throwWeapon(float playerVel);

    /*Funcion para modificar la direccion a la que apunta el arma
     * @param int i: Puede ser 1 o -1
     */
    void setDir(int i);
};

#endif /* WEAPON_H */

