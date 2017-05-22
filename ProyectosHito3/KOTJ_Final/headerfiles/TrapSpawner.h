/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TrapSpawner.h
 * Author: youjair
 *
 * Created on 4 de mayo de 2017, 20:10
 */

#ifndef TRAPSPAWNER_H
#define TRAPSPAWNER_H

#include <vector>
#include <cstdlib>
#include "Trampa.h"

class TrapSpawner {
public:
    TrapSpawner();
    TrapSpawner(const TrapSpawner& orig);
    virtual ~TrapSpawner();
    void crearTrampas();
    void borrarTrampas();
    void leerSpawnerPosition();
private:
    vector<vector<float>> spawnTraps;
};

#endif /* TRAPSPAWNER_H */

