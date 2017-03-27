/* 
 * File:   Temporizador.h
 * Author: daniel
 *
 * Created on 27 de marzo de 2017, 13:05
 */

#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "../Box2D/Box2D.h"

using namespace std;

class Temporizador {
public:
    Temporizador();
    Temporizador(int time, b2Vec2 position, int size);
    Temporizador(const Temporizador& orig);

    void Update();
    void Draw(sf::RenderWindow *window);
    void restartGame();

    virtual ~Temporizador();
private:

    sf::Clock chrono;
    sf::Font font;
    
    float maxTime;
    float currentTime;
    
    sf::Text *timeBoardSec;
    sf::Text *timeBoardMsec;
    
    b2Vec2 position;
    int size;

};

#endif /* TEMPORIZADOR_H */

