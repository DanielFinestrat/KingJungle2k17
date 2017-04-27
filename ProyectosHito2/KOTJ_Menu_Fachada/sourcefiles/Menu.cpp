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
    
    window = new sf::RenderWindow(VideoMode(1024, 600), "KingOfTheJungle 2k17 Turbo Power Edition", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);
}

void Menu::update() {
    int inc;
    for(int i = 0; i < options.size(); i++) {
        if(i == currentOpt) {
            inc = i*20;
            options[i]->setPosX(posX + 20);
            options[i]->setColor(0, 255, 0);
            triangle->setPos(posX-20, posY+16+inc);
            triangle->setAngle(90);    
        } else {
            options[i]->setPosX(posX);
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
    
    int i = 0;
    window->clear(sf::Color::Black);
    triangle->updateBody();
    window->draw(triangle->getShape());
    while(i < options.size()) {;
        options[i]->render(window);
        i++;
        
    }
    window->display();
}


int Menu::getCurrentOption() {
    return currentOpt;
}


Menu::~Menu() {
}

