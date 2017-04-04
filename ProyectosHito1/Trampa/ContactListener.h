/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContactListener.h
 * Author: youjair
 *
 * Created on 4 de abril de 2017, 16:17
 */

#include <iostream>
#include "Trampa.h"
#include "Box2D/Box2D.h"

#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

class ContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact);


};

#endif /* CONTACTLISTENER_H */

