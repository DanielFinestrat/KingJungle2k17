/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VisibleFigure.cpp
 * Author: amygwyllion
 * 
 * Created on 26 de abril de 2017, 12:47
 */

#include "../headerfiles/VisibleFigure.h"

VisibleFigure::VisibleFigure(float x, float y) {
    rectShape =  new sf::RectangleShape(sf::Vector2f(x,y));
}

VisibleFigure::VisibleFigure(float radius) {
    circShape =  new sf::CircleShape(radius);
}

VisibleFigure::VisibleFigure(const VisibleFigure& orig) {
}

VisibleFigure::~VisibleFigure() {
}

void VisibleFigure::rectShapeSetOrigin(float x, float y){
    rectShape->setOrigin(x,y);
}
void VisibleFigure::rectShapeSetPosition(float x, float y){
    rectShape->setPosition(sf::Vector2f(x,y));
}
void VisibleFigure::rectShapeSetFillColor(int r, int g, int b, int a){
    rectShape->setFillColor(sf::Color(r, g, b, a));
}
void VisibleFigure::rectShapeSetRotation(float angulo){
    rectShape->rotate(angulo);
}

void VisibleFigure::circShapeSetOrigin(float x, float y){
    circShape->setOrigin(x,y);
}
void VisibleFigure::circShapeSetPosition(float x, float y){
    circShape->setPosition(sf::Vector2f(x,y));
}
void VisibleFigure::circShapeSetFillColor(int r, int g, int b, int a){
    circShape->setFillColor(sf::Color(r, g, b, a));
}
void VisibleFigure::circShapeSetRotation(float angulo){
    circShape->rotate(angulo);
}
void VisibleFigure::circShapeSetRadius(float radius){
    circShape->setRadius(radius);
}


sf::RectangleShape VisibleFigure::getRectShape(){
    return *rectShape;
}

sf::CircleShape VisibleFigure::getCircShape(){
    return *circShape;
}

