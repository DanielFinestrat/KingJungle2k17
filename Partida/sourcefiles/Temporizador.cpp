/* 
 * File:   Temporizador.cpp
 * Author: daniel
 * 
 * Created on 27 de marzo de 2017, 13:05
 */

#include "../headerfiles/Temporizador.h"
#include "../headerfiles/Partida.h"

Temporizador::Temporizador() {
}

Temporizador::Temporizador(int time, b2Vec2 position, int size) {

    chrono.getElapsedTime();
    chrono.restart();

    maxTime = (float) time;

    if (!font.loadFromFile("resources/fonts/bits.ttf")) {
        cerr << "No encuentro la fuente (Clock)" << endl;
    }

    timeBoardSec = new sf::Text();
    timeBoardSec->setFont(font);
    timeBoardSec->setCharacterSize(size);
    timeBoardSec->setPosition(position.x - size/2, position.y);
    timeBoardSec->setString(to_string(maxTime));

    timeBoardMsec = new sf::Text();
    timeBoardMsec->setFont(font);
    timeBoardMsec->setCharacterSize(size/2);
    timeBoardMsec->setPosition(position.x + size/2 + 7, position.y + size/2);
    timeBoardMsec->setString(to_string(0));
}

Temporizador::Temporizador(const Temporizador& orig) {
}

Temporizador::~Temporizador() {
}

void Temporizador::Update() {
    currentTime = chrono.getElapsedTime().asSeconds();
    
    float fSeconds = maxTime -  currentTime;
    int iSeconds = maxTime -  currentTime;
    int iMiliseconds = (iSeconds - fSeconds) * -100;
    
    string sSeconds = to_string(iSeconds);
    string sMiliseconds = to_string(iMiliseconds);
    
    if(iSeconds < 10) sSeconds = "0" + sSeconds;
        
    if(iMiliseconds < 10) sMiliseconds = ":0" + sMiliseconds;
    else sMiliseconds = ":" + sMiliseconds;
    
    timeBoardSec->setString(sSeconds);
    timeBoardMsec->setString(sMiliseconds);
    
    if(iSeconds == 0 && iMiliseconds == 0) restartGame();
        
    
}

void Temporizador::Draw(sf::RenderWindow *window) {
    window->draw(*timeBoardSec);
    window->draw(*timeBoardMsec);
}

void Temporizador::restartGame(){
    chrono.restart();
    Partida *partida = Partida::getInstance();
    partida->respawn();
}