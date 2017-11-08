/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InnerClock.h
 * Author: amygwyllion
 *
 * Created on 27 de abril de 2017, 0:52
 */

#ifndef INNERCLOCK_H
#define INNERCLOCK_H

#include <SFML/Graphics.hpp>

class InnerClock {
public:
    InnerClock();
    InnerClock(const InnerClock& orig);
    virtual ~InnerClock();
    
    void restartClock();
    float getDeltaTimeAsSeconds();
    
private:
    
    sf::Clock clock;
    sf::Time deltaTime;

};

#endif /* INNERCLOCK_H */

