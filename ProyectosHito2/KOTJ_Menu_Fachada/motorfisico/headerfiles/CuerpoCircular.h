/* 
 * File:   CuerpoCircular.h
 * Author: danielfinestrat
 *
 * Created on 24 de abril de 2017, 12:03
 */

#ifndef CUERPOCIRCULAR_H
#define CUERPOCIRCULAR_H

#include <ctime>
#include <SFML/Graphics.hpp>
#include "../../Box2D/Box2D.h"
#include "../../headerfiles/Entidad.h"
#include <iostream>

class CuerpoCircular {
public:
    CuerpoCircular(b2World *world, b2Vec2 pos, float radio, float angle, Entidad* data); //Solo puede llamarse desde world
    virtual ~CuerpoCircular();
    void Destruir();
    
    void setVelocidadX(float x);
    void setVelocidadY(float y);
    void setVelocidad(float x, float y);
    void aplicarFuerza(float x, float y);
    void setAngulo(float angle);
    void setRadio(float radio);
    void setPosicion(float x,float y);
    void setUserData(Entidad* data);
    void setType(int type);
    void setFriction(float fric);
    void setRestitution(float rest);
    void setDensity(float den);
    void setSensor(bool sensor);
    void setActive(bool active);
    void setAwake(bool awake);
    void setDespertar(bool despertador);
    void setCategoryBits(short category);
    void setMaskBits(short mask);
    void setGravityScale(float gravityScale);
    
    float getAngulo();
    bool getActive();
    float getPosicionX();
    float getPosicionY();
    float getVelocidadX();
    float getVelocidadY();
    
private:
    b2Body *m_pBody;
};

#endif /* CUERPOCIRCULAR_H */

