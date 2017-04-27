/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   motorGrafico.h
 * Author: amygwyllion
 *
 * Created on 11 de abril de 2017, 20:17
 */

#ifndef MOTORGRAFICO_H
#define MOTORGRAFICO_H

#include <SFML/Graphics.hpp>
#include "../../headerfiles/Partida.h"

class motorGrafico {
public:
    motorGrafico();
    motorGrafico(const motorGrafico& orig);
    virtual ~motorGrafico();

    void setFramerateLimitOn(int framerate);
    void setMainCameraView();
    void setHudCameraView();
    void cameraSetTransform();
    
    void clearWindow();
    void eventListener();
    void updateWindow();
    void displayWindow();
    
    template <class T1> void draw(T1& object);
private:
    Partida *partida;
    sf::RenderWindow *window;
    sf::View *mainCamera;
    sf::View *hudCamera;
    sf::Event event;

};

#endif /* MOTORGRAFICO_H */

