/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StaticTexture.cpp
 * Author: pedro
 * 
 * Created on 5 de abril de 2017, 20:13
 */

#include "../headerfiles/StaticTexture.h"
using namespace std;
using namespace sf;
StaticTexture::StaticTexture() {textura = new Texture;}

void StaticTexture::loadTexture(string ruta) {
    
    if (!textura->loadFromFile(ruta)) {
        cerr << "Error cargando la imagen " << ruta << endl;
        exit(0);
    }
    textura->setSmooth(true);
}

sf::Texture* StaticTexture::getTexture() {
    return textura;
}

StaticTexture::~StaticTexture() {
}

