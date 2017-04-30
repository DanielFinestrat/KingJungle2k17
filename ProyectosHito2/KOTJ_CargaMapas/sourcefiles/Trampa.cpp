/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Trampa.cpp
 * Author: youjair
 * 
 * Created on 26 de marzo de 2017, 18:36
 */

#include "../headerfiles/Trampa.h"




#define WIDTH 800
#define HEIGHT 600
#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL
#define VELTRAP 5           //Velocidad que tendra la trampa

using namespace std;
using namespace sf;




//Trampa::Trampa(b2World *world, sf::Vector2f size, sf::Vector2f pos, int type, float angle ) {
Trampa::Trampa(Motorfisico *world, int sizeX, int sizeY, int posX, int posY, int type, float angle){
    tag = "Trampa";
    id = type;
    estado = false;
    roto = false; 
    m_SizeX = sizeX;
    m_SizeY = sizeY;
    iniPosX = posX;
    iniPosY = posY;
    contact = false;
    
    
    //b2BodyDef trapBody;
    cuerpo = Motorfisico::getInstance()->crearCuerpo(posX, posY, sizeX, sizeY,angle, this);
    cuerpo->setType(2);
    cuerpo->setSensor(true);
    
    m_Shape = new VisibleBody(posX, posY, sizeX, sizeY, "", false);   
}

Trampa::Trampa(const Trampa& orig) {
}

Trampa::~Trampa() {
}
void Trampa::activar(){
    int velY;
    
    if(estado ==false){ estado = true;
    
    velY = -VELTRAP;
    cuerpo->setVelocidadY(velY);
    }
    
}
void Trampa::desactivar(){
    int velY;
    
    if(estado == true){ estado = false;    
    velY = VELTRAP;
    cuerpo->setVelocidadY(velY);
    }
}
int Trampa::getID(){
    return id;
}
VisibleBody* Trampa::updateShape(){
    float angle = cuerpo->getAngulo();
    int posX = cuerpo->getPosicionX();
    int posY = cuerpo->getPosicionY();
    int velY;
            
    m_Shape->setPos(posX*PPM, posY*PPM);
    m_Shape->setAngle(angle);
    
    if(iniPosY >= posY*PPM+m_SizeY && cuerpo->getVelocidadY() < 0){
        velY = 0;
        cuerpo->setVelocidadY(velY);
    } else if(iniPosY <= posY*PPM && cuerpo->getVelocidadY() > 0){
        velY = 0;
        cuerpo->setVelocidadY(velY);
    }
    
    return *m_Shape;
}
bool Trampa::getEstado(){
    return estado;
}
/*
void Trampa::render(sf::RenderWindow *window){
    window->draw(*m_Shape);
}*/
void Trampa::startContact(){
    contact = true;
    std::cout<<"Has muerto."<<std::endl;
}
void Trampa::endContact(){
    contact = false;
}
