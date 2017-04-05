/* 
 * File:   motorgrafico.cpp
 * Author: danielfinestrat
 * 
 * Created on 5 de abril de 2017, 19:45
 */

#include "../headerfiles/motorgrafico.h"

motorgrafico::motorgrafico() {
    world = new b2World(b2Vec2(0.0f, 9.8f));
    world->SetContactListener(&myContactListener);
}

motorgrafico::motorgrafico(float gravedadY) {
    world = new b2World(b2Vec2(0.0f, gravedadY));
    world->SetContactListener(&myContactListener);
}

motorgrafico::motorgrafico(float gravedadX, float gravedadY) {
    world = new b2World(b2Vec2(gravedadX, gravedadY));
    world->SetContactListener(&myContactListener);
}

void motorgrafico::Update() {
    world->Step(TIMESTEP, VELITER, POSITER);
}

Cuerpo* motorgrafico::crearCuerpo(float posX, float posY, float sizeX, float sizeY) {
    return(new Cuerpo(world, b2Vec2(posX, posY), b2Vec2(sizeX, sizeY), 0));
}

Cuerpo* motorgrafico::crearCuerpo(float posX, float posY, float sizeX, float sizeY, float angulo) {
    return(new Cuerpo(world, b2Vec2(posX, posY), b2Vec2(sizeX, sizeY), angulo));
}

motorgrafico::~motorgrafico() {
}

