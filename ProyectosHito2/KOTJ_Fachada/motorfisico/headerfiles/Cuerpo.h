/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cuerpo.h
 * Author: youjair
 *
 * Created on 5 de abril de 2017, 19:17
 */
#include <ctime>
#include <SFML/Graphics.hpp>
#include "../../Box2D/Box2D.h"
#include <iostream>

#ifndef CUERPO_H
#define CUERPO_H

class Cuerpo {
public:
    Cuerpo(b2World *world, b2Vec2 pos, b2Vec2 size, float angle); //Solo puede llamarse desde world
    virtual ~Cuerpo();
    void setVelocidadX(float x);
    void setVelocidadY(float y);
    void setVelocidad(float x, float y);
    void aplicarFuerza(float x, float y);
    void setAngulo(float angle);
    void setTamanyo(float x, float y);
    void setPosicion(float x,float y);
    void setUserData();
    void setType(int type);
    void setFriction(float fric);
    void setRestitution(float rest);
    void setDensity(float den);
    void setSensor(bool sensor);
    void setDespertar(bool despertador);
    void setCategoryBits(short category);
    void setMaskBits(short mask);
    
    
    float getAngulo();
    float getPosicionX();
    float getPosicionY();
    float getVelocidadX();
    float getVelocidadY();

private:
    b2Body *m_pBody;
};

#endif /* CUERPO_H */

