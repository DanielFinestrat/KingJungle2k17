/* 
 * File:   Motorfisico.h
 * Author: danielfinestrat
 *
 * Created on 5 de abril de 2017, 19:45
 */

#ifndef MOTORGRAFICO_H
#define MOTORGRAFICO_H

#include "Cuerpo.h"
#include "ContactListener.h"

#define TIMESTEP 1.0f/15.f      //TIEMPO DE REFRESCO
#define VELITER 10              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION

class Motorfisico {
public:
    static Motorfisico* getInstance();

    void Update();
    Cuerpo* crearCuerpo(float posX, float posY, float sizeX, float sizeY, float angulo);
    Cuerpo* crearCuerpo(float posX, float posY, float sizeX, float sizeY);

    virtual ~Motorfisico();

private:
    b2World *world;
    ContactListener myContactListener;

    Motorfisico();
    Motorfisico(float gravedadY);
    Motorfisico(float gravedadX, float gravedadY);

};

#endif /* MOTORGRAFICO_H */

