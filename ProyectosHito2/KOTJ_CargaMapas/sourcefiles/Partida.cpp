/* 
 * File:   Partida.cpp
 * Author: daniel
 * 
 * Created on 26 de marzo de 2017, 13:13
 */

#include "../motorgrafico/headerfiles/Motorgrafico.h"
#include "../headerfiles/Partida.h"

using namespace sf;

static Partida* instance;

Partida::Partida() {
    usingKeyboard = false;
}

Partida* Partida::getInstance() {
    if (instance == NULL) instance = new Partida();
    return (instance);
}

void Partida::Input(int &e) {
    Motorgrafico::getInstance()->eventListener(e);
}

void Partida::erasePlayers() {
    for (int i = 0; i < players2Delete.size(); i++) {
        players2Delete.at(i)->die(players2Delete.at(i)->getDirMoving());
    }
    players2Delete.clear();
}

void Partida::eraseWeapons() {
    for (int i = 0; i < weapons2Delete.size(); i++) {
        delete(weapons2Delete.at(i));
    }
    weapons2Delete.clear();
}

void Partida::eraseBullets() {
    set<Bala*>::iterator itBala = bullets2Delete.begin();

    for (; itBala != bullets2Delete.end(); itBala++) {
        Bala* dyingBala = *itBala;
        if (dyingBala->explosion == true) {
            float posX = dyingBala->cuerpo->getPosicionX();
            float posY = dyingBala->cuerpo->getPosicionY();

            Explosion *nueva;
            nueva = new Explosion(posX * PPM, posY * PPM, 1.0f, 0.05f, 0.5f);
            worldExplo.insert(nueva);
        }
        worldBullets.erase(dyingBala);
        delete dyingBala;
        dyingBala = NULL;
    }
    bullets2Delete.clear();
}

void Partida::eraseExplo() {
    set<Explosion*>::iterator itExplo = explo2Delete.begin();
    set<Explosion*>::iterator itEnd = explo2Delete.end();

    for (; itExplo != itEnd; itExplo++) {
        Explosion* dyingExplo = *itExplo;
        worldExplo.erase(dyingExplo);
        delete dyingExplo;
        dyingExplo = NULL;
    }
    explo2Delete.clear();
}

void Partida::Erase() {
    eraseBullets();
    erasePlayers();
    eraseExplo();
    eraseWeapons();
}

void Partida::Update() {
    Motorfisico::getInstance()->Update();
    Motorgrafico::getInstance()->updateWindow();

    mapa->Update();
    factoriaArmas->Update();
    updateWeapons();
    updatePlayers(Motorgrafico::getInstance()->getFrameTime());
    updateBullets();
    updateExplo();

    cameraSetTransform();
}

void Partida::Render() {
    Motorgrafico::getInstance()->clearWindow();
    Motorgrafico::getInstance()->setMainCameraView();

    mapa->drawBackground();
    drawBullets();
    drawPlayers();
    drawWeapons();
    drawExplo();
    mapa->drawMap();

    Motorgrafico::getInstance()->setHudCameraView();
    Motorgrafico::getInstance()->drawTemporizador();
    Motorgrafico::getInstance()->displayWindow();
}

void Partida::drawPlayers() {
    for (int i = 0; i < worldPlayer.size(); i++) {
        Motorgrafico::getInstance()->draw(worldPlayer.at(i)->getPlayerSprite());
    }
}

void Partida::drawWeapons() {
    for (int i = 0; i < worldWeapons.size(); i++) {
        if (worldWeapons.at(i) != NULL) Motorgrafico::getInstance()->draw((worldWeapons.at(i)->m_vBody->getShape()));
    }
}

void Partida::drawBullets() {
    set<Bala*>::iterator itBala = worldBullets.begin();
    set<Bala*>::iterator endBala = worldBullets.end();
    for (; itBala != endBala; ++itBala) {
        Bala* renderBala = *itBala;
        Motorgrafico::getInstance()->draw(renderBala->getBodyShape()->getShape());
    }
}

void Partida::drawExplo() {
    set<Explosion*>::iterator itExplo = worldExplo.begin();
    set<Explosion*>::iterator endExplo = worldExplo.end();
    for (; itExplo != endExplo; ++itExplo) {
        Explosion* renderExplo = *itExplo;
        Motorgrafico::getInstance()->draw(renderExplo->getBodyShape()->getCircleShape());
    }
}

int Partida::findKeyboardControlador() {
    int index = -1;

    for (int i = 0; i < worldControlador.size(); i++) {
        if (worldControlador.at(i)->tipo.compare("Keyboard") == 0) {
            index = i;
            break;
        }
    }
    return index;
}

int Partida::findControladorWithId(int id) {
    int index = -1;

    for (int i = 0; i < worldControlador.size(); i++) {
        if (worldControlador.at(i)->tipo.compare("Joystick") == 0 && worldControlador.at(i)->id == id) {
            index = i;
            break;
        }
    }

    return index;
}

void Partida::checkJoysticksConnected() {
    Joystick joystickManager;
    for (int i = 0; i < 4; i++) {
        if (joystickManager.isConnected(i)) {
            addPlayerJoystick(i);
        }
    }
}

void Partida::addPlayerJoystick(int id) {
    //Para saber si la tenemos que añador
    bool add = true;

    //Comprobamos si existe el mando y actualizamos la condición
    for (int i = 0; i < worldControlador.size() && add; i++) {
        if (worldControlador.at(i)->tipo.compare("Joystick") == 0 && worldControlador.at(i)->id == id) add = false;
    }

    //Añadimos en funcion de la condición
    if (add && worldControlador.size() < 4) {
        PlayerJoystick* p = new PlayerJoystick(id);
        worldControlador.push_back(p);
    }
}

void Partida::addPlayerKeyboard() {
    if (worldControlador.size() < 4) worldControlador.push_back(new PlayerKeyboard());
}

void Partida::respawn() {
    for (int i = 0; i < worldPlayer.size(); i++) {
        Player* player = worldPlayer.at(i);
        player->setPosition((i + 1) * screenWidth / 5, screenHeight - 100);
        player->respawn();
    }
}

void Partida::updatePlayers(Time frameTime) {
    for (int i = 0; i < worldPlayer.size(); i++) {
        worldPlayer.at(i)->update(Motorgrafico::getInstance()->getFrameTime());
    }
}

void Partida::updateWeapons() {
    for (int i = 0; i < worldWeapons.size(); i++) {
        if (worldWeapons.at(i) != NULL) worldWeapons.at(i)->update();
    }
}

void Partida::updateBullets() {
    set<Bala*>::iterator itBala = worldBullets.begin();
    set<Bala*>::iterator endBala = worldBullets.end();
    for (; itBala != endBala; ++itBala) {
        Bala* updateBala = *itBala;
        updateBala->Update_Shape();
    }

}

void Partida::updateExplo() {
    set<Explosion*>::iterator itExplo = worldExplo.begin();
    set<Explosion*>::iterator endExplo = worldExplo.end();
    for (; itExplo != endExplo; ++itExplo) {
        Explosion* updateBala = *itExplo;
        updateBala->Update();
    }
}

void Partida::cameraSetTransform() {
    Motorgrafico::getInstance()->cameraSetTransform();
}

bool Partida::getUsingKeyboard() {
    return usingKeyboard;
}

void Partida::setUsingKeyboard(bool state) {
    usingKeyboard = state;
}

void Partida::loadMap() {
    checkJoysticksConnected();

    mapa = new Mapa();
    mapa->leerMapa(mapa->mapaSelva);

    factoriaArmas = new Weaponspawner();
    Motorgrafico::getInstance()->getTemporizador()->stop(false);
}

Partida::~Partida() {
}