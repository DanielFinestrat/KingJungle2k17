
/* 
 * File:   VisibleBody.cpp
 * Author: pedro
 * 
 * Created on 11 de abril de 2017, 17:07
 */

#include "VisibleBody.h"
#include <PI.h>


VisibleBody::VisibleBody(){}

VisibleBody::VisibleBody(float x, float y, float w, float h, std::string path, bool centerOrigin) {
    posX = x;
    posY = y;
    height = h;
    width = w;
    texPath = path;
    angle = 0;
    circle.setRadius(0);
   
    rectangle.setPosition(posX, posY);
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setScale(1, 1);
    
    if (centerOrigin)rectangle.setOrigin(sf::Vector2f(width/2.0f, height/2.0f));
    else rectangle.setOrigin(sf::Vector2f(0, 0));

    tex = Resources::getInstance();
    if(texPath!="") rectangle.setTexture(&tex->getTexture(texPath), 0);
}

VisibleBody::VisibleBody(float x, float y, float rad, std::string path){
    posX = x;
    posY = y;
    radius = rad;
    angle = 0;
    
    circle.setPosition(posX, posY);
    circle.setRadius(radius);
    circle.setOrigin(radius/2.0f,radius/2.0f);
    circle.setScale(1,1);
    
    tex = Resources::getInstance();
    if(texPath!="") circle.setTexture(&tex->getTexture(texPath));
}

void VisibleBody::setRect(float posX, float posY, float width, float height){
    IntRect *myRect = new IntRect(posX, posY, width, height);
    rectangle.setTextureRect(*myRect);
}

void VisibleBody::updateBody() {
    rectangle.setOrigin(width/2.0f, height/2.0f);
    rectangle.setPosition(posX, posY);
    rectangle.setRotation(angle);
}

void VisibleBody::setPos(float x, float y) {
    posX = x;
    posY = y;
    rectangle.setPosition(posX,posY);
}

void VisibleBody::setCirclePos(float x, float y){
    posX = x;
    posY = y;
    circle.setPosition(posX,posY);
}

void VisibleBody::setCircleOrigin(float x, float y){
    circle.setOrigin(x,y);
}

void VisibleBody::setAngle(float a) {
    angle = a;
}

void VisibleBody::setDim(float w, float h) {
    height = h;
    width = w;
}

void VisibleBody::setTex(std::string path) {
    texPath = path;
    if(circle.getRadius() == 0)
        rectangle.setTexture(&tex->getTexture(texPath));
    else
        circle.setTexture(&tex->getTexture(texPath));
}

void VisibleBody::setScale(int sX, int sY) {
    rectangle.setScale(sX, sY);
}

void VisibleBody::setRot(float angle){
    rectangle.rotate(angle);
}

void VisibleBody::setCircleRot(float angle){
    circle.rotate(angle);
}

void VisibleBody::setCircleRadius(float rad){
    radius = rad;
    circle.setRadius(radius);
}

void VisibleBody::setColor(int r, int g, int b, int a) {
    Color c = Color(r,g,b,a);
    rectangle.setFillColor(c);
}

void VisibleBody::setTexRect(int x, int y, int w, int h) {
    IntRect myRect = IntRect(x, y, w, h);
    rectangle.setTextureRect(myRect);
}

float VisibleBody::getPosX() {
    return posX;
}

float VisibleBody::getPosY() {
    return posY;
}

float VisibleBody::getHeight() {
    return height;
}

float VisibleBody::getWidth() {
    return width;
}

std::vector<float> VisibleBody::getPos() {
    std::vector<float> vec(2);
    vec[1] = posX;
    vec[2] = posY;
    return vec;
}

std::vector<float> VisibleBody::getDim() {
    std::vector<float> vec(2);
    vec[1] = width;
    vec[2] = height;
    return vec;
}

std::string VisibleBody::getTexPath() {
    return texPath;
}

sf::RectangleShape VisibleBody::getShape() {
    return rectangle;
}

sf::CircleShape VisibleBody::getCircleShape(){
    return circle;
}

sf::FloatRect VisibleBody::getBounds() {
    return rectangle.getGlobalBounds();
}

VisibleBody::~VisibleBody() {
}

