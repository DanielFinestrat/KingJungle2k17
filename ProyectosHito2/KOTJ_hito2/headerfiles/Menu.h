
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
     * Constructor de menu principal
     * std::vector<Texto> op: Vector con las opciones que se desplegaran en el menu
     * float x: Posicion inicial en X del menu
     * float y: Posicion inicial en Y del menu
     */
    Menu(std::vector<Texto*> op, float x, float y);
    
    /*
     * Constructor de menu de opciones de partida
     * std::vector<Texto> op: Vector con las opciones que se desplegaran en el menu
     * float x: Posicion inicial en X del menu
     * float y: Posicion inicial en Y del menu
     */
    Menu(std::vector<Texto*> op, float x, float y, int r, float t, int mode);
    
    /*
     * Funcion que dibuja un menu generico
     */
    void render();
    
    /*
     * Funcion que dibuja el menu de las opciones de partida
     */
    void renderGameMenu();
        
    /*
     * Funcion que desplaza a abajo la seleccion de opcion
     */
    void goDown();
    
    /*
     * Funcion que incrementa el numero de rondas (+1)
     */
    void increaseRounds();
    
    /*
     * Funcion que incrementa el tiempo (+10)
     */
    
    void increaseTime();
    /*
     * Funcion que incrementa el modo (+1)
     */
    void increaseMode();
    
    /*
     * Funcion que decrementa el numero de rondas (-1)
     */
    void decreaseRounds();
    
    /*
     * Funcion que decrementa el tiempo (-10)
     */
    void decreaseTime();
    
    /*
     * Funcion que decrementa el modo (-1)
     */
    void decreaseMode();
    
    
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
    void gameUpdate();
    
    /*
     * Funcion que gestiona la entrada de teclado
     */
    void input(int &state, Menu* menu);
    
    virtual ~Menu();
private:
    std::vector<Texto*> options;
    std::vector<string> modes;
    Texto* trounds, * ttime, * tmode;
    int currentOpt, rounds, mode;
    float posX, posY, time;
    VisibleBody* triangle, * triangle1, *  triangle2, *  rectangle;
};

#endif /* MENU_H */

