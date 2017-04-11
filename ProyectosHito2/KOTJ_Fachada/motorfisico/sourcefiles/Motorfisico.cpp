/* 
 * File:   Motorfisico.cpp
 * Author: danielfinestrat
 * 
 * Created on 5 de abril de 2017, 19:45
 */

#include "../headerfiles/Motorfisico.h"

Motorfisico::Motorfisico() {
    world = new b2World(b2Vec2(0.0f, 9.8f));
    world->SetContactListener(&myContactListener);
}

Motorfisico::Motorfisico(float gravedadY) {
    world = new b2World(b2Vec2(0.0f, gravedadY));
    world->SetContactListener(&myContactListener);
}

Motorfisico::Motorfisico(float gravedadX, float gravedadY) {
    world = new b2World(b2Vec2(gravedadX, gravedadY));
    world->SetContactListener(&myContactListener);
}

void Motorfisico::Update() {
    world->Step(TIMESTEP, VELITER, POSITER);
}

Cuerpo* Motorfisico::crearCuerpo(float posX, float posY, float sizeX, float sizeY) {
    return(new Cuerpo(world, b2Vec2(posX, posY), b2Vec2(sizeX, sizeY), 0));
}

Cuerpo* Motorfisico::crearCuerpo(float posX, float posY, float sizeX, float sizeY, float angulo) {
    return(new Cuerpo(world, b2Vec2(posX, posY), b2Vec2(sizeX, sizeY), angulo));
}

Motorfisico::~Motorfisico() {
}

