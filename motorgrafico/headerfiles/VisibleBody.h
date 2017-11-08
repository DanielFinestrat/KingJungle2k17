
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
    
    VisibleBody();
    
    /**
     * Constructor de un cuerpo visible cuadrado
     * @param float posX: Posicion en X del objeto
     * @param float posY: Posicion en Y del objeto
     * @param float height: Altura del objeto en pixeles
     * @param float width: Anchhura del objeto en pixeles
     * @param string textPath: ruta de textura
     * @param bool centerOrigin: si quieres centrar el origen al medio
     */
    VisibleBody(float posX, float posY, float width, float height, std::string texPath, bool centerOrigin);
    
    /**
     * Constructor de un cuerpo visible circular
     * @param float posX: Posicion en X del objeto
     * @param float posY: Posicion en Y del objeto
     * @param float radius: Radio del objeto
     */
    VisibleBody(float posX, float posY, float radius, std::string texPath);
    
    void setRect(float posX, float posY, float width, float height);
    
    /**
     * Funcion que modifica la posicion del objeto
     * @param float posX: Posicion en X del objeto
     * @param float posY: Posicion en Y del objeto
     */
    void setPos(float posX, float posY);
    
    /**
     * Funcion que modifica la posicion del objeto circulo
     * @param float posX: Posicion en X del objeto
     * @param float posY: Posicion en Y del objeto
     */
    void setCirclePos(float posX, float posY);
    
    /**
     * Funcion que modifica el origen del shape del objeto circulo
     * @param float posX: Posicion en X del objeto
     * @param float posY: Posicion en Y del objeto
     */
    void setCircleOrigin(float posX, float posY);
    
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
     * Funcion que modifica el angulo de rotacion del objeto
     * @param float angle: Angulo de rotacion
     */
    void setRot(float angle);
    
     /*
     * Funcion que modifica el angulo de rotacion del objeto circulo
     * @param float angle: Angulo de rotacion
     */
    void setCircleRot(float angle);
    
    /**
     * Establece un nuevo radio para el objeto circulo
     * @param float rad : Nuevo radio del objeto circulo
     */
    void setCircleRadius(float rad);
    
    /**
     * Funcion para modificar la rotacion del objeto
     * @param float angle: angulo de rotacion EN GRADOS.
     */
    void setAngle(float angle);
    
    /**
     * Funcion para cambiar el color del objeto
     * @param r cantidad de rojo de 0 a 255
     * @param g cantidad de verde de 0 a 255
     * @param b cantidad de azul de 0 a 255
     * @param a canal alfa del color
     */
    void setColor(int r, int g, int b, int a);
    /*
     * Funcion que especifica el rectangulo a pintar de una textura
     * @param int x: Posicion X inicial del rectangulo
     * @param int y: Posicion Y inicial del rectangulo
     * @param int w: Ancho del rectangulo
     * @param int h: Alto del rectangulo
     */
    void setTexRect(int x, int y, int w, int h);
    
    //Funcion que devuelve la posicion del objeto
    std::vector<float> getPos();
    
    //Funcion que devuelve la posicion en X del objeto
    float getPosX();
    
    //Funcion que devuelve la posicion en Y del objeto
    float getPosY();
    
    //Funcion que devuelve las dimensiones del objeto
    std::vector<float> getDim();
    
    //Funcion que devuelve la altura del objeto
    float getHeight();
    
    //Funcion que devuelve la anchura del objeto
    float getWidth();
    
    //Funcion que devuelve la ruta de la textura del objeto
    std::string getTexPath();
    
    //Funcion que actualiza el objeto
    void updateBody();
    
    sf::RectangleShape getShape();
    
    sf::CircleShape getCircleShape();
    
    //Funcion que devuelve las esquinas del objeto
    sf::FloatRect getBounds();
    
    virtual ~VisibleBody();
private:
    float posX, posY, height, width, radius, angle;
    std::string texPath;
    sf::RectangleShape rectangle;
    sf::CircleShape circle;
    Resources* tex;
};

#endif /* VISIBLEBODY_H */

