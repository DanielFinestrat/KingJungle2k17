/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InnerClock.cpp
 * Author: amygwyllion
 * 
 * Created on 27 de abril de 2017, 0:52
 */

#include "../headerfiles/InnerClock.h"

InnerClock::InnerClock() {
}

InnerClock::InnerClock(const InnerClock& orig) {
}

InnerClock::~InnerClock() {
}

void InnerClock::restartClock(){
    deltaTime = clock.restart();
}

float InnerClock::getDeltaTimeAsSeconds(){
    return deltaTime.asSeconds();
}

