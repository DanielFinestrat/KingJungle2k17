/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cuerpo.h
 * Author: youjair
 *
 * Created on 5 de abril de 2017, 19:17
 */
#include <ctime>
#include <SFML/Graphics.hpp>
#include "../../Box2D/Box2D.h"
#include <iostream>

#ifndef CUERPO_H
#define CUERPO_H

class Cuerpo {
public:
    Cuerpo();
    Cuerpo(const Cuerpo& orig);
    virtual ~Cuerpo();
private:
    b2FixtureDef m_Fixture;
    b2BodyDef   m_pBody;
    b2PolygonShape  m_Shape;
};

#endif /* CUERPO_H */

