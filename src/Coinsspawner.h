
/* 
 * File:   Coinsspawner.h
 * Author: amygwyllion
 *
 * Created on 1 de mayo de 2017, 16:44
 */

#ifndef COINSSPAWNER_H
#define COINSSPAWNER_H

#include "Entidad.h"
#include "Coin.h"
#include "motorfisico/Cuerpo.h"
#include "motorgrafico/VisibleBody.h"
#include "motorgrafico/Animation.h"
#include "motorgrafico/SpriteAnimated.h"
#include "motorgrafico/InnerClock.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"

class Coinsspawner {
public:
    Coinsspawner();
    Coinsspawner(const Coinsspawner& orig);
    virtual ~Coinsspawner();
    
    void leerCoins();
    void leerSpawnerPosition();
    void cargarCoins();
    void deleteCoins();
    
    void Update();
    void checkIfUsed();
private:
    
    struct datosCoin {
        int indice;
        int valor;
        int rareza;
        Animation* animation;
    };
    
    const string coinsFile = "./resources/datos/coins.xml";
    
    Texture texture;
    SpriteAnimated* coinSprite;
    Animation *coinAnimation;
    VisibleBody* m_vBody;
    Cuerpo* cuerpo;
    float posX, posY;
    float sizeX, sizeY;
    float scaleX, scaleY;
    float value;
    
    vector< vector<int> > spawnCoins;
    vector<datosCoin> datosCoins;
    vector<Coin*> coins;
    
    InnerClock* clock;
    const float respawnTime = 20.0f;
    float currentTime;

};

#endif /* COINSSPAWNER_H */

