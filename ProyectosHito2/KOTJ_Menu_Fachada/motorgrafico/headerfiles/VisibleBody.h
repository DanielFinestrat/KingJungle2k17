/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VisibleBody.h
 * Author: pedro
 *
 * Created on 11 de abril de 2017, 17:07
 */

#ifndef VISIBLEBODY_H
#define VISIBLEBODY_H

#include "../headerfiles/resources.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class VisibleBody {
public:
 
    /* Constructor de un cuerpo visible 
     * @param float posX: Posicion en X del objeto
     * @param float posY: Posicion en Y del objeto
     * @param float height: Altura del objeto en pixeles
     * @param float width: Anchhura del objeto en pixeles
     */
    VisibleBody(float posX, float posY, float width, float height, std::string texPath);
    
    /*Funcion que modifica la posicion del objeto
     * @param float posX: Posicion en X del objeto
     * @param float posY: Posicion en Y del objeto
     */
    void setPos(float posX, float posY);
    
    /*Funcion que modifica las dimensiones del objeto 
     * @param float height: Altura del objeto
     * @param float width: Anchura del objeto
     */
    void setDim(float width, float height);
    
    /*Funcion que modifica la textura
     * @param std::string texPath: ruta de la textura
     */
    void setTex(std::string texPath);
    
    /*
     * Funcion que modifica la escala 
     * @param int sX: Escala en X
     * @param int sY: Escala en Y
     */
    void setScale(int sX, int sY);
    
    /*
     * Funcion para modificar la rotacion del objeto
     * @param float angle: angulo de rotacion EN GRADOS.
     */
    void setAngle(float angle);
    
    /*
     * Funcion que devuelve la posicion del objeto
     */
    std::vector<float> getPos();
    
    /*
     * Funcion que devuelve la posicion en X del objeto
     */
    float getPosX();
    
    /*
     * Funcion que devuelve la posicion en Y del objeto
     */
    float getPosY();
    
    /*
     * Funcion que devuelve las dimensiones del objeto
     */
    std::vector<float> getDim();
    
    /*
     * Funcion que devuelve la altura del objeto
     */
    float getHeight();
    
    /*
     * Funcion que devuelve la anchura del objeto
     */
    float getWidth();
    
    /*
     * Funcion que devuelve la ruta de la textura del objeto
     */
    std::string getTexPath();
    
    /*
     * Funcion que actualiza el objeto
     * @param float posX: Posicion en X nueva del objeto
     * @param float posY: Posicion en Y nueva del objeto
     * @param float angle: Angulo de la rotacion
     */
    void updateBody();
    
    /* Funcion para rendereizar el el objeto
     * @param sf::RenderWindow window: Ventana en la que se va a dibujar el objeto
     */
    sf::RectangleShape getShape();
    
    /*Funcion que devuelve las esquinas del objeto
     */
    sf::FloatRect getBounds();
    
    
    virtual ~VisibleBody();
private:
    float posX, posY, height, width, angle;
    std::string texPath;
    sf::RectangleShape rectangle;
    Resources* tex;
};

#endif /* VISIBLEBODY_H */

