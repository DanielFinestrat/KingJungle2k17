
/* 
 * File:   Coin.cpp
 * Author: amygwyllion
 * 
 * Created on 30 de abril de 2017, 18:40
 */

#include "headerfiles/Coin.h"
#include "headerfiles/Partida.h"


Coin::Coin(float posx, float posy, int m_value, Animation* animation) {
    tag = "Coin";
    
    posX = posx;
    posY = posy;
    sizeX = 15;
    sizeY = 30;
    scaleX = 0.3;
    scaleY = 0.4;
    value = m_value;
    inPossession = false;
        
    m_vBody = new VisibleBody(posX, posY, sizeX, sizeY, "", false);
    
    currentAnimation = animation;
    
    coinSprite = new SpriteAnimated(seconds(0.1), true, false);
    coinSprite->setPosition(m_vBody->getPosX()-5,m_vBody->getPosY()-5);
    coinSprite->setAnimation(*currentAnimation);
    
    setScale(scaleX,scaleY);
    
}

Coin::Coin(const Coin& orig) {
}

Coin::~Coin() {
}

void Coin::setValue(int coinValue){
    value = coinValue;
}

int Coin::getValue(){
    return value;
}

void Coin::setColor(int r, int g, int b, int a){
    coinSprite->setColor(Color(r,g,b,a));
}

void Coin::setPosition(float posx, float posy){
    posX = posx;
    posY = posy;
    m_vBody->setPos(posX,posY);
    coinSprite->setPosition(m_vBody->getPosX(),m_vBody->getPosY());
}

float Coin::getPositionX(){
    return m_vBody->getPosX();
}

float Coin::getPositionY(){
    return m_vBody->getPosY(); 
}

void Coin::setScale(float scalex, float scaley){
    scaleX = scalex;
    scaleY = scaley;
    coinSprite->setScale(scaleX,scaleY);

}

float Coin::getScaleX(){
    return scaleX;
}

float Coin::getScaleY(){
    return scaleY;
}

void Coin::setPossession(bool value){
    inPossession = value;
}

bool Coin::getInPossession(){
    return inPossession;
}

void Coin::playAnimation(){
    coinSprite->play(*currentAnimation);
}

VisibleBody& Coin::getVisibleBody(){
    return *m_vBody;
}

float Coin::getWidth(){
    return m_vBody->getWidth();
}

float Coin::getHeight(){
    return m_vBody->getHeight();
}

void Coin::update(Time frameTime){
    coinSprite->update(frameTime);
    playAnimation();
}

SpriteAnimated& Coin::getCoinSprite(){
    return *coinSprite;
}
