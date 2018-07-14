/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TrapSpawner.cpp
 * Author: youjair
 * 
 * Created on 4 de mayo de 2017, 20:10
 */

#include <vector>
#include <cstdlib>

#include "TrapSpawner.h"
#include "Partida.h"

TrapSpawner::TrapSpawner() {
    leerSpawnerPosition();
    crearTrampas();
}

TrapSpawner::TrapSpawner(const TrapSpawner& orig) {
}

TrapSpawner::~TrapSpawner() {
}


void TrapSpawner::crearTrampas(){
    int  type, timeAct, timeDes;
    float posX, posY, sizeX, sizeY;
    vector<float> trapDate;
    Trampa* trap = NULL;
    for(int i = 0; i < spawnTraps.size(); i++){
        trapDate = spawnTraps.at(i);
        posX = trapDate.at(0);
        posY = trapDate.at(1);
        type = trapDate.at(2);
        sizeX = trapDate.at(3);
        sizeY = trapDate.at(4);
        timeDes = trapDate.at(5);
        timeAct = trapDate.at(6);
        trap = new Trampa(sizeX, sizeY, posX, posY, type,0, timeDes, timeAct);
        
        Partida::getInstance()->worldTraps.push_back(trap);
        
    }    
        
    
}
void TrapSpawner::borrarTrampas(){
    for (int i = 0; i < Partida::getInstance()->worldTraps.size(); i++) {
        Trampa* trap = Partida::getInstance()->worldTraps.at(i);
        if (trap != NULL) {
            Partida::getInstance()->traps2Delete.push_back(Partida::getInstance()->worldTraps.at(i));
            Partida::getInstance()->worldTraps.at(i) = NULL;
        }
    }    
    
    
}
void TrapSpawner::leerSpawnerPosition(){
    spawnTraps = Partida::getInstance()->mapa->getSpawnTrampas();
}
