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

using namespace std;
using namespace sf;

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

    Texture weapon_texture;

    //Variables para controlar la cadencia de disparo
    sf::Clock deltaClock;
    float difTime;
    sf::Time dt;
    time_t lastShot;

    std::set<Bala*> balasAEliminar;
    std::set<Bala*> listadoBalas;

    sf::Vector2f m_Size;
    b2Body *m_pBody;
    sf::RectangleShape *m_Shape;

    /*Constructor del objeto arma
     * @param b2world world: mundo en el que se encuentran todos los objetos
     * @param vector2f size: tamaño del arma
     * @param vector2f pos: posicion del arma
     * @param float shoot_cadence: Disparos por segundo 
     * @param int BPS: Balas por disparo
     * @param int ammo: Municion del arma
     */
    Weapon(b2World *world, sf::Vector2f size, sf::Vector2f pos, float shoot_cadence, int BPS, int ammo, int recoil_, bool parabola, bool explosivo);
    ~Weapon();

    /*Se encarga de actualizar las posiciones de los elementos del arma*/
    void update();

    /*Se encarga de actualizar la posicion cuando un jugador tiene el arma
     * @param b2Vec2 pos: vector posicion a la que se movera el arma
     */
    void update(b2Vec2 pos);

    /*Crea balas para añadirlas en el array y seguidamente llamar a la función disparo de Bala
     * @param b2World world: mundo en el que se van a crear las balas
     */
    int shoot();

    /*Funcion que renderiza el arma
     * @param RenderWindow window: Ventana en la que se muestra el programa
     */
    void render(sf::RenderWindow *window);

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

