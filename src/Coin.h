
/* 
 * File:   Coin.h
 * Author: amygwyllion
 *
 * Created on 30 de abril de 2017, 18:40
 */

#ifndef COIN_H
#define COIN_H

#include "Entidad.h"
#include "motorfisico/Cuerpo.h"
#include "motorgrafico/headerfiles/VisibleBody.h"
#include "motorgrafico/headerfiles/Animation.h"
#include "motorgrafico/headerfiles/SpriteAnimated.h"

class Coin : public Entidad {
public:
    Coin(float, float, int, Animation* );
    Coin(const Coin& orig);
    virtual ~Coin();
    
    void playAnimation();
    
    void setValue(int);
    int getValue();
    void setColor(int, int, int, int);
    void setPosition(float,float);
    float getPositionX();
    float getPositionY();
    void setScale(float, float);
    float getScaleX();
    float getScaleY();
    void setPossession(bool);
    bool getInPossession();
    VisibleBody& getVisibleBody();
    float getWidth();
    float getHeight();
    
    void update(Time frameTime);
    SpriteAnimated& getCoinSprite();
    
    
private:
    
    struct datosCoin {
        int indice;
        string nombre;
        int valor;
        float rareza;
    };
    
    VisibleBody* m_vBody;
    Texture texture;
    SpriteAnimated* coinSprite;
    Animation coinAnimation;
    Animation* currentAnimation;
    
    Cuerpo* cuerpo;
    float posX, posY;
    float sizeX, sizeY;
    float scaleX, scaleY;
    float value;
    bool inPossession;
    
    

};

#endif /* COIN_H */

