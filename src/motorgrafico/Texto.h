
/* 
 * File:   Texto.h
 * Author: pedro
 *
 * Created on 19 de abril de 2017, 19:15
 */

#ifndef TEXTO_H
#define TEXTO_H

#include "resources.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>

class Texto {
public:
    
    /* Constructor de un texto
     * @param std::string text: Cadena que sera el texto actual a mostrar
     * @param float posX: Posicion en X del objeto
     * @param float posY: Posicion en Y del objeto
     * @param int size: Tamaño de la fuente
     * @param std::string path: Ruta del fichero de la fuente del texto
     * @param int r: Representa la tonalidad en rojo.
     * @param int g: Representa la tonalidad en verde.
     * @param int b: Representa la tonalidad en azul.
     */
    Texto(std::string text, int size, std::string path, int r, int g, int b);
    
    /* Constructor de un texto que mostrara un numero entero
     * @param int i: Numero que sera el texto actual a mostrar
     * @param float posX: Posicion en X del objeto
     * @param float posY: Posicion en Y del objeto
     * @param int size: Tamaño de la fuente
     * @param std::string path: Ruta del fichero de la fuente del texto
     * @param int r: Representa la tonalidad en rojo.
     * @param int g: Representa la tonalidad en verde.
     * @param int b: Representa la tonalidad en azul.
     */
    Texto(int i, int size, std::string path, int r, int g, int b);
    
    /* Constructor de un texto que mostrara un numero float
     * @param float i: Numero que sera el texto actual a mostrar
     * @param float posX: Posicion en X del objeto
     * @param float posY: Posicion en Y del objeto
     * @param int size: Tamaño de la fuente
     * @param std::string path: Ruta del fichero de la fuente del texto
     * @param int r: Representa la tonalidad en rojo.
     * @param int g: Representa la tonalidad en verde.
     * @param int b: Representa la tonalidad en azul.
     */
    Texto(float i, int size, std::string path, int r, int g, int b);
    
     /*Funcion que modifica la posicion del objeto
     * @param float posX: Posicion en X del objeto
     * @param float posY: Posicion en Y del objeto
     */
    void setPos(float posX, float posY);
    
    /*Funcion que modifica el tamaño de la  fuente del objeto
     * @param int i: Tamaño de la fuente que tendra el objeto
     */
    void setSize(int i);
    
    /*
     * Funcion que modifica el texto del objeto
     * @param std::string s: Cadena de texto que añadiremos
     */
    void setTexto(std::string s);
    void setTexto(int i);
    void setTexto(float i);
    
    /*
     * Funcion que modifica el color del objeto
     * @param int r: Representa la tonalidad en rojo.
     * @param int g: Representa la tonalidad en verde.
     * @param int b: Representa la tonalidad en azul.
     */
    void setColor(int r, int g, int b);
    
    /*
     * Funcion que modifica la ruta de la fuente del objeto
     * @param std::string p: Ruta de la fuente que se va a utilizar
     */
    void setFont(std::string p);
    
    /*
     * Funcion que modifica la escala del texto
     * @param float sX: Escala en X del objeto
     * @param float sY: Escala en Y del objeto
     */
    void setScale(float sX, float sY);
    
    /*
     * Funcion que devuelve la cadena de texto actual del objeto
     */
    std::string getTexto();
    
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
     * Funcion que devuelve el tamaño de la fuente
     */
    int getSize();
    
     /*
     * Funcion que devuelve la ruta de la fuente del objeto
     */
    std::string getFontPath();
    
    /*
     * Metodo que devuelve el objeto dibujable
     */
    sf::Text getDrawable();
    
    /*
     * Funcion que devuelve el tamaño de un texto
     */
    int getStringLength();
    
    virtual ~Texto();
private:
    sf::Text text;
    sf::Color color;
    std::string string, fontPath;
    int size;
    float posX, posY;
    Resources* font;
};

#endif /* TEXTO_H */

