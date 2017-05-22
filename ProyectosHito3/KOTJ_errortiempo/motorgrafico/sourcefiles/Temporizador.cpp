/* 
 * File:   Temporizador.cpp
 * Author: daniel
 * 
 * Created on 27 de marzo de 2017, 13:05
 */

#include "../headerfiles/Temporizador.h"
#include "../../headerfiles/Partida.h"

Temporizador::Temporizador() {
}

Temporizador::Temporizador(int time, float posx, float posy, int size) {

    chrono.getElapsedTime();
    chrono.restart();

    maxTime = (float) time;
    m_posx = posx;
    m_posy = posy;

    timeBoardSec = new sf::Text();
    timeBoardSec->setFont(Resources::getInstance()->getFont(Resources::getInstance()->myFont));
    timeBoardSec->setCharacterSize(size);

    ostringstream stm;
    stm << maxTime;
    timeBoardSec->setString(stm.str());

    timeBoardMsec = new sf::Text();
    timeBoardMsec->setFont(Resources::getInstance()->getFont(Resources::getInstance()->myFont));
    timeBoardMsec->setCharacterSize(size / 2);
    timeBoardMsec->setString(":00");

    setPosition();
    stop(true);
}

Temporizador::Temporizador(const Temporizador& orig) {
}

Temporizador::~Temporizador() {
}

void Temporizador::Update() {
    if (!stopped) {
        currentTime = chrono.getElapsedTime().asSeconds();

        float fSeconds = maxTime - currentTime;
        int iSeconds = maxTime - currentTime;
        int iMiliseconds = (iSeconds - fSeconds) * -100; //100 a 0
        iMiliseconds = iMiliseconds * 60 / 100; //60 a 0

        ostringstream stm;
        stm << iSeconds;
        string sSeconds = stm.str();
        stm.clear();
        stm.str("");
        stm << iMiliseconds;
        string sMiliseconds = stm.str();

        if (iSeconds < 10) sSeconds = "0" + sSeconds;

        if (iMiliseconds < 10) sMiliseconds = ":0" + sMiliseconds;
        else sMiliseconds = ":" + sMiliseconds;

        timeBoardSec->setString(sSeconds);
        timeBoardMsec->setString(sMiliseconds);

        setPosition();

        if (iSeconds <= 0 && iMiliseconds <= 0) restartGame();
        else if (iSeconds < 0) restartGame();
    } else {
        chrono.restart();
    }

}

sf::Text Temporizador::getTimeBoardSec() {
    return *timeBoardSec;
}

sf::Text Temporizador::getTimeBoardMsec() {
    return *timeBoardMsec;
}

void Temporizador::Draw(sf::RenderWindow *window) {
    window->draw(*timeBoardSec);
    window->draw(*timeBoardMsec);
}

void Temporizador::restartGame() {
    chrono.restart();
    Partida *partida = Partida::getInstance();

    for (int i = 0; i < partida->worldPlayer.size(); i++) {
        partida->players2Delete.push_back(partida->worldPlayer.at(i));
    }
    
    partida->finalLevelTextPrepared = true;

    /*partida->loadMap();
    partida->respawn();*/
}

void Temporizador::setPosition() {

    timeBoardSec->setPosition(m_posx - (timeBoardSec->getGlobalBounds().width / 2), m_posy);

    float mposX = timeBoardSec->getGlobalBounds().left + timeBoardSec->getGlobalBounds().width + (timeBoardMsec->getGlobalBounds().width / 4);
    float mposY = timeBoardSec->getGlobalBounds().top + timeBoardSec->getGlobalBounds().height - (timeBoardMsec->getGlobalBounds().height * 1.675);

    timeBoardMsec->setPosition(mposX, mposY);

}

void Temporizador::setBasePosition(float posx, float posy) {
    m_posx = posx;
    m_posy = posy;
}

void Temporizador::setScale(float newScaleX, float newScaleY) {
    timeBoardSec->setScale(newScaleX, newScaleY);
    timeBoardMsec->setScale(newScaleX, newScaleY);
}

void Temporizador::restart() {
    chrono.restart();
    currentTime = maxTime;
    ostringstream stm;
    stm << maxTime;
    timeBoardSec->setString(stm.str());
    timeBoardMsec->setString(":00");
}

void Temporizador::stop(bool stop) {
    stopped = stop;
}