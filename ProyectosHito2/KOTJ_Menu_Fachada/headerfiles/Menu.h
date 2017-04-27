/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   menu.h
 * Author: pedro
 *
 * Created on 25 de abril de 2017, 14:27
 */

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include "../motorgrafico/headerfiles/Texto.h"
#include "../motorgrafico/headerfiles/VisibleBody.h"

class Menu {
public:
    
    sf::RenderWindow* window;
    /*
     * Constructor de menus
     * std::vector<Texto> op: Vector con las opciones que se desplegaran en el menu
     * float x: Posicion inicial en X del menu
     * float y: Posicion inicial en Y del menu
     */
    Menu(std::vector<Texto*> op, float x, float y);
    void render();
        
    /*
     * Funcion que desplaza a abajo la seleccion de opcion
     */
    void goDown();
    
    /*
     * Funcion que desplaza a arriba la seleccion de opcion
     */
    void goUp();
    
    /*
     * Funcion que devuelve la opcion seleccionada actualmente
     */
    int getCurrentOption();
    
    /*
     * Funcion que actualiza el menu
     */
    void update();
    
    /*
     * Funcion que gestiona la entrada de teclado
     *
    void input();
     */
    
    
    virtual ~Menu();
private:
    std::vector<Texto*> options;
    int currentOpt;
    float posX, posY;
    VisibleBody* triangle;
    
};

#endif /* MENU_H */

