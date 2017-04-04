/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Trampa.h
 * Author: youjair
 *
 * Created on 26 de marzo de 2017, 18:36
 */

#ifndef TRAMPA_H
#define TRAMPA_H

#include <ctime>
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include <iostream>
#include "filters.h"




using namespace std;

class Trampa {
public:
    Trampa(b2World *world, sf::Vector2f size, sf::Vector2f pos, int type, float angle);
    Trampa(const Trampa& orig);
    virtual ~Trampa();
    int getID();
    bool getEstado();
    bool getRoto();
    void activar();
    void desactivar();
    void startContact();
    void endContact();
    void render(sf::RenderWindow *window);
    sf::RectangleShape updateShape();
private:
    int id;
    bool estado; //Activado(true) o desactivado(false)
    bool roto; //Roto (true) intacto (false)
    b2Vec2 iniPos;
    bool contact;
    
    
    sf::Texture texture; //textura de la trampa 
    
    //Variables de tiempo para controlar la cadencia de disparo
    sf::Clock deltaClock;
    int difTime;
    sf::Time dt;
    time_t lastActive;
    
    //Tamanyos
    sf::Vector2f m_Size;
    b2Body *m_pBody;
    sf::RectangleShape *m_Shape;

};

#endif /* TRAMPA_H */

