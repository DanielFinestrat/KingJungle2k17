
/* 
 * File:   Weaponspawner.h
 * Author: danielfinestrat
 *
 * Created on 28 de abril de 2017, 19:23
 */

#ifndef WEAPONSPAWNER_H
#define WEAPONSPAWNER_H

#include <vector>
#include "Weapon.h"
#include "tinyxml/headerfiles/tinystr.h"
#include "tinyxml/headerfiles/tinyxml.h"
#include "motorgrafico/InnerClock.h"

using namespace std;

class Weaponspawner {
public:

    Weaponspawner();
    virtual ~Weaponspawner();

    void leerArmas();
    void leerSpawnerPosition();
    
    void cargarArmas();
    void cargarArmas(int indice);
    
    void Update();
    void deleteNotUsedWeapon();
    void deleteNotPossessedWeapons();

private:

    struct rect {
        float x;
        float y;
        float w;
        float h;
    };

    struct datosArma {
        int indice;
        int bpd;
        int cargador;
        int rareza;
        int rango;
        int recoil;
        float recoiltime;
        bool parabola;
        bool explosivo;
        rect rectangulo;
    };

    const string weaponFile = "./resources/datos/armas.xml";
    
    vector< vector<int> > spawnArmas;
    vector<datosArma> datosArmas;
    
    InnerClock* clock;
    const float respawnTime = 20.0f;
    float currentTime;

};

#endif /* WEAPONSPAWNER_H */

