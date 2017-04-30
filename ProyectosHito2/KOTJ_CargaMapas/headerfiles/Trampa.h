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


#include <stdio.h>
#include <math.h>
#include <iostream>
#include <set>
#include <vector>
#include "Entidad.h"
#include "../motorfisico/headerfiles/Cuerpo.h"
#include "../motorfisico/headerfiles/Motorfisico.h"
#include "../motorgrafico/headerfiles/VisibleBody.h"


using namespace std;

class Trampa : public Entidad{
public:
    
    /**
     * Constructor del objeto Bala
     * @param mundo Motorfisico*: mundo en el que estan todos los objetos
     * @param sizeX int: ancho de la trampa
     * @param sizeY int: alto de la trampa
     * @param posX int: posicion inicial X
     * @param posY int: posicion inicial Y
     * @param type int: tipo de trampa
     * @param angle float: angulo de la trampa
     */
    Trampa(Motorfisico *world, int sizeX, int sizeY, int posX, int posY, int type, float angle);
    Trampa(const Trampa& orig);
    virtual ~Trampa();
    int getID();
    /**
     * Devuelve si esta activada (true) o desactivada (false)
     * @return 
     */
    bool getEstado();
    bool getRoto();
    void activar();
    void desactivar();
    void startContact();
    void endContact();
    //void render(sf::RenderWindow *window);
    VisibleBody* updateShape();
private:
    int id;
    bool estado; //Activado(true) o desactivado(false)
    bool roto; //Roto (true) intacto (false)
    int iniPosX;
    int iniPosY;
    bool contact;
    
    Cuerpo *cuerpo;
    
   
    
    //Tamanyos
    int m_SizeX;
    int m_SizeY;
    VisibleBody *m_Shape;

};

#endif /* TRAMPA_H */

