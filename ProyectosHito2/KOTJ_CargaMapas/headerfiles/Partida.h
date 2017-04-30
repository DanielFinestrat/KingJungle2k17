
/* 
 * File:   Partida.h
 * Author: daniel
 *
 * Created on 26 de marzo de 2017, 13:13
 */

#ifndef PARTIDA_H
#define PARTIDA_H

#include <vector>
#include "../motorfisico/headerfiles/Motorfisico.h"
#include "../motorgrafico/headerfiles/Temporizador.h"
#include "Weaponspawner.h"
#include "Platform.h"
#include "Weapon.h"
#include "Bala.h"
#include "Explosion.h"
#include "PlayerJoystick.h"
#include "PlayerKeyboard.h"
#include "Mapa.h"

using namespace std;

#define screenWidth 1024
#define screenHeight 600

#define TIMESTEP 1.0f/15.f      //TIEMPO DE REFRESCO
#define VELITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA POSICION

class Motorgrafico;

class Partida {
public:
    
    Mapa *mapa;
    Weaponspawner* factoriaArmas;

    vector<Weapon*> worldWeapons;
    set<Bala*> worldBullets;
    set<Explosion*> worldExplo;
    vector<Player*> worldPlayer;
    vector<Controlador*> worldControlador;

    vector<Player*> players2Delete;
    vector<Weapon*> weapons2Delete;
    set<Bala*> bullets2Delete;
    set<Explosion*> explo2Delete;
    
    static Partida* getInstance();

    void Input(int &e);
    void Update();
    void Erase();
    void Render();

    void drawPlatforms();
    void drawPlayers();
    void drawWeapons();
    void drawBullets();
    void drawExplo();

    void eraseBullets();
    void erasePlayers();
    void eraseWeapons();
    void eraseExplo();

    int findKeyboardControlador();
    int findControladorWithId(int id);
    void checkJoysticksConnected();
    void addPlayerJoystick(int id);
    void addPlayerKeyboard();
    void respawn();

    void updatePlayers(Time frameTime);
    void updateBullets();
    void updateWeapons();
    void updateExplo();

    void cameraSetTransform();

    bool getUsingKeyboard();
    void setUsingKeyboard(bool state);

    void loadMap();
    virtual ~Partida();

private:
    
    Motorgrafico *mg;
    bool usingKeyboard;
    
    Partida();

};

#endif /* PARTIDA_H */

