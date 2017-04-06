/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StaticTexture.h
 * Author: pedro
 *
 * Created on 5 de abril de 2017, 20:13
 */

#ifndef STATICTEXTURE_H
#define STATICTEXTURE_H
#include <iostream>
#include <SFML/Graphics.hpp>

class StaticTexture {
public:
     sf::Texture* textura;
    StaticTexture();
    
    /*Constructor de una textura que no tendra animacion
     * @param string ruta: ruta del archivo de imagen a cargar para la textura
     */
    void loadTexture(std::string ruta);
    
    sf::Texture* getTexture();
   
    virtual ~StaticTexture();
private:
   
};

#endif /* STATICTEXTURE_H */

