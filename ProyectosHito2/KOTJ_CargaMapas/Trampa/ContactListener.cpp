/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContactListener.cpp
 * Author: youjair
 * 
 * Created on 4 de abril de 2017, 16:17
 */

#include "ContactListener.h"


void ContactListener::BeginContact(b2Contact* contact){
    
    
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    
    if(bodyUserDataA)
        static_cast<Trampa*>(bodyUserDataA)->startContact();
    
    
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if(bodyUserDataB)
        static_cast<Trampa*>(bodyUserDataB)->startContact();
   
}

