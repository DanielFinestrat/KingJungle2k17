
/* 
 * File:   Temporizador.h
 * Author: daniel
 *
 * Created on 27 de marzo de 2017, 13:05
 */

#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

#include <iostream>
#include <sstream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;

class Temporizador {
public:
    Temporizador();
    Temporizador(int time, float posx, float posy, int size);
    Temporizador(const Temporizador& orig);

    void Update();
    sf::Text getTimeBoardSec();
    sf::Text getTimeBoardMsec();
    void Draw(sf::RenderWindow *window);
    void restartGame();
    void setPosition();
    void setBasePosition(float posx, float posy);
    void setScale(float newScaleX, float newScaleY);

    virtual ~Temporizador();
private:

    sf::Clock chrono;
    sf::Font font;
    
    float maxTime;
    float currentTime;
    
    sf::Text *timeBoardSec;
    sf::Text *timeBoardMsec;
    
    float m_posx;
    float m_posy;
    int size;

};

#endif /* TEMPORIZADOR_H */

