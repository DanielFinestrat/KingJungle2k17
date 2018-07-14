
/* 
 * File:   Motorfisico.h
 * Author: danielfinestrat
 *
 * Created on 5 de abril de 2017, 19:45
 */

#ifndef MOTORGRAFICO_H
#define MOTORGRAFICO_H

#include "Cuerpo.h"
#include "CuerpoCircular.h"
#include "ContactListener.h"
#include "../../Entidad.h"

#define TIMESTEP 1.0f/15.f      //TIEMPO DE REFRESCO
#define VELITER 10              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION

class Motorfisico {
public:
    static Motorfisico* getInstance();

    void Update();
    Cuerpo* crearCuerpo(float posX, float posY, float sizeX, float sizeY, float angulo, Entidad* data);
    Cuerpo* crearCuerpo(float posX, float posY, float sizeX, float sizeY, Entidad* data);
    CuerpoCircular* crearCuerpoCircular(float posX, float posY, float radio, float angulo, Entidad* data);
    CuerpoCircular* crearCuerpoCircular(float posX, float posY, float radio, Entidad* data);

    virtual ~Motorfisico();

private:
    b2World *world;
    ContactListener myContactListener;

    Motorfisico();
    Motorfisico(float gravedadY);
    Motorfisico(float gravedadX, float gravedadY);

};

#endif /* MOTORGRAFICO_H */

