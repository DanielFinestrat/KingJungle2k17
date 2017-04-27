/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VisibleFigure.h
 * Author: amygwyllion
 *
 * Created on 26 de abril de 2017, 12:46
 */

#ifndef VISIBLEFIGURE_H
#define VISIBLEFIGURE_H

#include <SFML/Graphics.hpp>

class VisibleFigure {
public:
    VisibleFigure(float, float);
    VisibleFigure(float);
    
    VisibleFigure(const VisibleFigure& orig);
    virtual ~VisibleFigure();
    
    void rectShapeSetOrigin(float, float);
    void rectShapeSetPosition(float, float);
    void rectShapeSetFillColor(int, int, int, int);
    void rectShapeSetRotation(float);
    
    void circShapeSetOrigin(float, float);
    void circShapeSetPosition(float, float);
    void circShapeSetFillColor(int, int, int, int);
    void circShapeSetRotation(float);
    void circShapeSetRadius(float);
    
    sf::RectangleShape getRectShape();
    sf::CircleShape getCircShape();
    
private:
    
    sf::RectangleShape *rectShape;
    sf::CircleShape *circShape;

};

#endif /* VISIBLEFIGURE_H */

