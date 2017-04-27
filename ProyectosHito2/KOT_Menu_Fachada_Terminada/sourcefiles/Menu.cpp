/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.cpp
 * Author: pedro
 * 
 * Created on 25 de abril de 2017, 14:27
 */

#include "../headerfiles/Menu.h"
#include "../motorgrafico/headerfiles/Motorgrafico.h"

Menu::Menu(std::vector<Texto*> op, float x, float y) {
    options = op;
    currentOpt = 0;
    posX = x;
    posY = y;
    
    triangle = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/triangle.png");
   
    int inc;
    for(int i = 0; i < options.size(); i++) {
        inc = i*20;
        options[i]->setPos(posX, posY+inc);        
    }
}

void Menu::update() {
    int inc;
    for(int i = 0; i < options.size(); i++) {
        inc = i*20;
        if(i == currentOpt) {
            options[i]->setPos(posX + 20, posY+inc);
            options[i]->setColor(0, 255, 0);
            triangle->setPos(posX-20, posY+16+inc);
            triangle->setAngle(90);    
        } else {
            options[i]->setPos(posX, posY+inc);
            options[i]->setColor(255, 0, 0);
        }
    }
}

void Menu::goDown() {
    
    if (currentOpt == options.size()-1) {
        currentOpt = 0;
    } else {
        
        currentOpt++;
    }
}

void Menu::goUp() {
    
    if (currentOpt == 0) {
        currentOpt = options.size() - 1;
    } else {
        currentOpt--;
    }
}

void Menu::render() {
    
    Motorgrafico::getInstance()->clearWindow();
    Motorgrafico::getInstance()->setMainCameraView();
    
    int i = 0;
    
    triangle->updateBody();
    Motorgrafico::getInstance()->draw(triangle->getShape());
    while(i < options.size()) {
        Motorgrafico::getInstance()->draw(options[i]->getDrawable());
        i++;
    }
    Motorgrafico::getInstance()->displayWindow();
}

void Menu::input(int &state, Menu* menu) {
    Motorgrafico::getInstance()->eventListener(state, menu);
}

int Menu::getCurrentOption() {
    return currentOpt;
}


Menu::~Menu() {
}

