
/* 
 * File:   Bala.h
 * Author: angel
 *
 * Created on 16 de marzo de 2017, 20:43
 */

#ifndef BALA_H
#define BALA_H

#include "Entidad.h"
#include "motorfisico/Cuerpo.h"
#include "motorfisico/Motorfisico.h"
#include "motorgrafico/headerfiles/VisibleBody.h"

class Bala : public Entidad {
public:
    
    bool explosion;

    float posInicialX;
    float posInicialY;
    float maxDist;
    
    Cuerpo *cuerpo;
    VisibleBody *shape;

    /**
     * Constructor del objeto Bala
     * @param mundo b2World*: mundo en el que estan todos los objetos
     * @param x float: ancho de la bala
     * @param y float: alto de la bala
     * @param position Vector2f: posicion inicial de la bala
     * @param explo bool: activar la explosion al eliminar la bala
     */
    Bala(float x, float y, float posx, float posy, bool explo, int rango, bool balaVisible);

    /**
     * Actualiza el RectangleShape del objeto
     */
    void Update_Shape();

    /** 
     * Le añade una fuerza a la bala en la direccion selecciona afectandole la gravedad
     * @param fuerza float: fuerza a la que se dispara
     * @param angulo float: direccion del movimiento (grados)
     */
    void Disparar_Parabola(float fuerza, float angulo);

    /**
     * Le aplica una velocidad constane a la bala en la direccion seleccionada
     * @param velocidad float: velocidad de la bala
     * @param angulo float: direccion del movimiento (grados)
     */
    void Disparar(float velocidad, float angulo);
    
    
    void Contact(void* punt, string tipo);
    
    /**
     * 
     * @return el shape de la bala (VisibleBody) 
     */
    
    VisibleBody* getBodyShape();

    /**
     * Elimina de memoria las variables de la bala
     */
    ~Bala();
};

#endif /* BALA_H */

