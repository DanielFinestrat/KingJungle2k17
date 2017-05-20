
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
#include <sstream>
#include <string>
#include "../motorgrafico/headerfiles/Texto.h"
#include "../motorgrafico/headerfiles/VisibleBody.h"
#include "../motorgrafico/headerfiles/Fondo.h"


class Menu {
public:
    
    sf::RenderWindow* window;
    /*
     * Constructor de menu principal
     * std::vector<Texto> op: Vector con las opciones que se desplegaran en el menu
     * float x: Posicion inicial en X del menu
     * float y: Posicion inicial en Y del menu
     */
    Menu(std::vector<Texto*> op, int x, int y);
    
    /*
     * Constructor de menu de opciones de partida
     * std::vector<Texto> op: Vector con las opciones que se desplegaran en el menu
     * int x: Posicion inicial en X del menu
     * int y: Posicion inicial en Y del menu
     * int r: numero de rondas por defecto
     * float t: tiempo por defecto
     * int m: modo de juego por defecto
     */
    Menu(std::vector<Texto*> op, int x, int y, int r, float t, int m);
    
    /*
     * Constructor de menu de opciones generales
     * std::vector<Texto> op: Vector con las opciones que se desplegaran en el menu
     * int x: Posicion inicial en X del menu
     * int y: Posicion inicial en Y del menu
     * int vm: Volumen de musica
     * int vfx: volumen de efectos
     */
    Menu(std::vector<Texto*> op, int x, int y, int vm, int vfx);
    
    /*
     * Funcion que dibuja un menu generico
     */
    void render();
    
    /*
     * Funcion que dibuja el menu de las opciones de partida
     */
    void renderGameMenu();
    void renderOptionsMenu();
        
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
     * Funcion que incrementa el volumen de musica en +10
     */
    void increaseMusicVol();
    
    /*
     * Funcion que incrementa el volumen de efectos en +10
     */
    void increaseFXVol();
    
    /*
     * Funcion que decrementa el volumen de musica en -10
     */
    void decreaseMusicVol();
    
    /*
     * Funcion que decrementa el volumen de efectos en -10
     */
    void decreaseFXVol();
    
    
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
    void optionsUpdate();
    
    int getTiempo();
    int getRounds();
    int getMode();
    
    /*
     * Funcion que gestiona la entrada de teclado
     */
    void input(int &state, Menu* menu);
    
    virtual ~Menu();
private:
    std::vector<Texto*> options;
    std::vector<string> modes;
    Texto* trounds, * ttime, * tmode, * tmVol, * tfxVol;
    int currentOpt, rounds, mode, time, musicVol, fxVol;
    float posX, posY;
    VisibleBody* puntero, * puntero1, *  puntero2, *  rectangle;
    Fondo* fondo;
};

#endif /* MENU_H */

