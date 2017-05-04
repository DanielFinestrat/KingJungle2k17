
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
#include "../motorgrafico/headerfiles/VisibleBody.h"

using namespace std;

class Trampa : public Entidad {
public:

    /**
     * Constructor del objeto Trampa
     * @param sizeX int: ancho de la trampa
     * @param sizeY int: alto de la trampa
     * @param posX int: posicion inicial X
     * @param posY int: posicion inicial Y
     * @param type int: tipo de trampa (0 = pinchos, 1 = zona mortal, 2 = palanca, 3 = tnt, 4 = nitro )
     * @param angle float: angulo de la trampa
     * @param time int : tiempo activo
     */
    Trampa(int sizeX, int sizeY, int posX, int posY, int type, float angle, int time);
    Trampa(const Trampa& orig);
    virtual ~Trampa();
    int getID();
    /**
     * Devuelve si esta activada (true) o desactivada (false)
     * @return 
     */
    bool getEstado();
    bool getRoto();
    Cuerpo* getCuerpo();
    VisibleBody* getVBody();
    void activar();
    void desactivar();
    void update();
    
private:
    int id; //0 pinchos, 1 zona de muerte solida, 2 zona de muerte atravesable, 3 tnt, 4 nitroglicerina, 5 palanca, 6 placa de presion
    bool estado; //Activado(true) o desactivado(false)
    bool roto; //Roto (true) intacto (false)
    int iniPosX;
    int iniPosY;
    int time;
    Cuerpo *cuerpo;

    //Tamanyos
    int m_SizeX;
    int m_SizeY;
    VisibleBody *m_vBody;

};

#endif /* TRAMPA_H */

