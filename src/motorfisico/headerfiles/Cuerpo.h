
/* 
 * File:   Cuerpo.h
 * Author: youjair
 *
 * Created on 5 de abril de 2017, 19:17
 */
#ifndef CUERPO_H
#define CUERPO_H

#include "../../Box2D/Box2D.h"
#include "../../Entidad.h"

class Cuerpo {
public:
    Cuerpo(b2World *world, b2Vec2 pos, b2Vec2 size, float angle, Entidad* data); //Solo puede llamarse desde world
    virtual ~Cuerpo();
    void Destruir();
    
    void setVelocidadX(float x);
    void setVelocidadY(float y);
    void setVelocidad(float x, float y);
    void aplicarFuerza(float x, float y);
    void setAngulo(float angle);
    void setTamanyo(float x, float y);
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

#endif /* CUERPO_H */