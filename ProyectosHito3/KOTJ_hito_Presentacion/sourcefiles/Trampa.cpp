
/* 
 * File:   Trampa.cpp
 * Author: youjair
 * 
 * Created on 26 de marzo de 2017, 18:36
 */

#include "../headerfiles/Trampa.h"
#include "../motorfisico/headerfiles/Motorfisico.h"


#define VELTRAP 3 //Velocidad que tendra la trampa

using namespace std;
using namespace sf;

Trampa::Trampa(float sizeX, float sizeY, float posX, float posY, int type, float angle, int tiempo) {
    tag = "Trampa";
    id = type;
    estado = false;
    roto = false;
    m_SizeX = sizeX;
    m_SizeY = sizeY;
    iniPosX = posX;
    iniPosY = posY;
    time = tiempo;
    reloj.restartClock();
    difTime = 0;

    cuerpo = Motorfisico::getInstance()->crearCuerpo(posX + sizeX/2, posY+sizeY/2, sizeX, sizeY, angle, this);
    cuerpo->setCategoryBits(CATEGORY_TRAMPA);
    m_vBody = new VisibleBody(posX+sizeX/2, posY+sizeY/2, sizeX, sizeY, "", true);

    
    switch (id) {
            case 0: //Pinchos
                cuerpo->setType(2);
                cuerpo->setMaskBits(MASK_TRAMPA1);//Colisiona con jugadores
                cuerpo->setSensor(true);
                //activar();
                m_vBody->setTex(Resources::getInstance()->spikes);
                break;
            case 1: //Zona de muerte solida
                cuerpo->setType(0);
                cuerpo->setMaskBits(MASK_TRAMPA2);//Colisiona con balas y jugadores
                m_vBody->setTex("");
                break;
            case 2: //Zona de muerte atravesable
                cuerpo->setType(0);
                cuerpo->setMaskBits(MASK_TRAMPA1);
                cuerpo->setSensor(true);
                m_vBody->setTex("");
                break; 
            case 3: //TNT
                cuerpo->setType(1);
                cuerpo->setMaskBits(MASK_TRAMPA2);
                m_vBody->setTex("");
                break;
            case 4: //Nitroglicerina
                cuerpo->setType(1);
                cuerpo->setMaskBits(MASK_TRAMPA2);
                m_vBody->setTex("");
                break;
            case 5: //Palanca
                cuerpo->setType(0);
                cuerpo->setMaskBits(MASK_TRAMPA1);
                cuerpo->setSensor(true);
                m_vBody->setTex("");
                break;
            case 6: //Placa de presion
                cuerpo->setType(0);
                cuerpo->setMaskBits(MASK_TRAMPA1);
                cuerpo->setSensor(true);
                m_vBody->setTex("");
                break;
    }
}

Trampa::Trampa(const Trampa& orig) {
}

Trampa::~Trampa() {
    cuerpo->Destruir();
    delete cuerpo;
    cuerpo = NULL;
    delete m_vBody;
    m_vBody = NULL;
}
void Trampa::activar() {
    int velY;

    if (!estado) {
        estado = true;
        switch(id){
                case 0:
                    velY = -VELTRAP;
                    cuerpo->setVelocidadY(velY);
                    break;
                case 3:
                    roto = true;
                    break;
                case 4:
                    roto = true;
                    break;
              //  case 5:
               // case 6:
                default:
                    break;
        }                    
                                
        
    }

}

void Trampa::desactivar() {
    int velY;
    
    
    
    if (estado) {
        estado = false;
        switch(id){
                case 0:
                    velY = VELTRAP;
                    cuerpo->setVelocidadY(velY);
                    break;
              // case 5:
               // case 6:
                default:
                    break;
                                
                                
        }
    }

}

int Trampa::getID() {
    return id;
}

void Trampa::update() {
    float angle = cuerpo->getAngulo();
    float posX = cuerpo->getPosicionX();
    float posY = cuerpo->getPosicionY();
    float velY;

    m_vBody->setPos(posX*PPM, posY*PPM);
    m_vBody->setAngle(angle);
    //cout<<difTime<<endl;
    
    reloj.restartClock();
    difTime += reloj.getDeltaTimeAsSeconds();

    if(estado == false && difTime >= 9){
        activar();
        difTime = 0;
    } else if(estado == true && difTime >= time){
        desactivar();
        difTime = 0;
    }

    if (iniPosY >= posY * PPM + m_SizeY/2  && cuerpo->getVelocidadY() < 0) {
        velY = 0;
        cuerpo->setVelocidadY(velY);
    } else if (iniPosY <= posY * PPM - m_SizeY/2 && cuerpo->getVelocidadY() > 0) {
        velY = 0;
        cuerpo->setVelocidadY(velY);
    }
    
}

bool Trampa::getEstado() {
    return estado;
}


Cuerpo* Trampa::getCuerpo(){
    return(this->cuerpo);
}

VisibleBody* Trampa::getVBody(){
    return(this->m_vBody);
}

void Trampa::Contact(void* punt, string tipo){

}
