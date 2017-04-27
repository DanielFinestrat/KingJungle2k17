/* 
 * File:   Partida.h
 * Author: daniel
 *
 * Created on 26 de marzo de 2017, 13:13
 */

#ifndef PARTIDA_H
#define PARTIDA_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "../Box2D/Box2D.h"
#include "Temporizador.h"
#include "Platform.h"
#include "Weapon.h"
#include "Bala.h"
#include "Explosion.h"
#include "PlayerJoystick.h"
#include "ContactListener.h"
#include "PlayerKeyboard.h"
#include "IAController.h"
#include "Console.h"

#include "tinystr.h"
#include "tinyxml.h"

using namespace std;

#define screenWidth 1024
#define screenHeight 600

#define TIMESTEP 1.0f/15.f      //TIEMPO DE REFRESCO
#define VELITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA POSICION

class Partida {
public:
    b2World *world;
    ContactListener myContactListener;
    sf::RenderWindow *window;
    
    sf::View *mainCamera;
    sf::View *hudCamera;

    vector<Platform*> worldPlatforms;
    vector<Weapon*> worldWeapons;
    set<Bala*> worldBullets;
    set<Explosion*> worldExplo;
    vector<Player*> worldPlayer;
    vector<Controlador*> worldControlador;

    set<Bala*> bullets2Delete;
    vector<Player*> players2Delete;
    set<Explosion*> explo2Delete;
    
    vector<vector<int>> spawnPlayer;
    vector<vector<int>> esquinasMapa;
    
    Temporizador *temporizador;
    Clock frameClock;

    int ***_tilemap;
    sf::Texture map_texture;
    vector<sf::Sprite*> map_sprites;
    
    static Partida* getInstance();

    void IA();
    
    void cargarXML();
    void guardarCapas(TiXmlElement* map);
    void guardarObj(TiXmlElement* map);
    
    void Input();
    void Update();
    void Erase();
    void Render();

    void drawPlatforms();
    void drawPlayers();
    void drawWeapons();
    void drawBullets();
    void drawExplo();
    void drawMap();
    
    void eraseBullets();
    void erasePlayers();
    void eraseExplo();
    
    int findKeyboardControlador();
    int findControladorWithId(int id);
    void checkJoysticksConnected();
    void addPlayerJoystick(int id);
    void addPlayerKeyboard();
    void addPlayerIA();
    void respawn();
    
    void updatePlayers(Time frameTime);
    void updateBullets();
    void updateWeapons();
    void updateExplo();

    void cameraSetTransform();
    void cargarTiles(int capa, int y, int x);
    void loadMap();
    virtual ~Partida();

private:
    
    Partida();
    Partida(const Partida& orig);
    bool usingKeyboard;

    Console console;
};

#endif /* PARTIDA_H */

