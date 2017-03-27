/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Animation.cpp
 * Author: amygwyllion
 * 
 * Created on 8 de marzo de 2017, 10:41
 */

#include "Animation.h"
using namespace sf;
using namespace std;

Animation::Animation() {
    texture = NULL;
}

Animation::Animation(const Animation& orig) {
}

Animation::~Animation() {
}

void Animation::setSpriteSheet(const Texture& new_texture)
{
    texture = &new_texture;
}

const Texture* Animation::getSpriteSheet() const
{
    return texture;
}

void Animation::addFrame(IntRect new_frame)
{
    frames.push_back(new_frame);
}

const IntRect& Animation::getFrame(size_t index) const
{
    return frames[index];
}

size_t Animation::getSize() const
{
    return frames.size();
}
