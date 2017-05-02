/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Texto.cpp
 * Author: pedro
 * 
 * Created on 19 de abril de 2017, 19:15
 */

#include "../headerfiles/Texto.h"

Texto::Texto(std::string t, int s, std::string p, int r, int g, int b) {
    string = t;
    size = s;
    fontPath = p;
    color.r = r;
    color.g = g;
    color.b = b;
    font = Resources::getInstance();

    text.setFont(font->getFont(fontPath));
    text.setCharacterSize(size);
    text.setPosition(posX, posY);
    text.setString(string);
	text.setColor(color);
    //text.setFillColor(color);
    text.setScale(1,1);
}

void Texto::setPos(float x, float y) {
    posX = x;
    posY = y;
    text.setPosition(posX, posY);
}

void Texto::setSize(int i) {
    size = i;
    text.setCharacterSize(size);
}

void Texto::setTexto(std::string s){
    string = s;
    text.setString(string);
}

void Texto::setColor(int r, int g, int b) {
    color.r = r;
    color.g = g;
    color.b = b;
	text.setColor(color);
    //text.setFillColor(color);
}

void Texto::setFont(std::string p) {
    fontPath = p;
    text.setFont(font->getFont(fontPath));
}

void Texto::setScale(float sX, float sY) {
    text.setScale(sX, sY);
}

std::string  Texto::getTexto() {
    return string;
}

std::vector<float> Texto::getPos(){
    std::vector<float> vec(2);
    vec[1] = posX;
    vec[2] = posY;
    return vec;
}
    
float Texto::getPosX() {
    return posX;
}

float Texto::getPosY() {
    return posY;
}

 int Texto::getSize() {
     return size;
 }
 
std::string Texto::getFontPath() {
    return fontPath;
}

sf::Text Texto::getDrawable() {
    return text;
}

Texto::~Texto() {
}


