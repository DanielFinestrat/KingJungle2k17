
/* 
 * File:   Weaponspawner.cpp
 * Author: danielfinestrat
 * 
 * Created on 28 de abril de 2017, 19:23
 */

#include "headerfiles/Weaponspawner.h"
#include "headerfiles/Partida.h"
#include "motorgrafico/headerfiles/Motorgrafico.h"

Weaponspawner::Weaponspawner() {
    leerArmas();
    leerSpawnerPosition();
    cargarArmas();

    currentTime = respawnTime;

    clock = new InnerClock();
    clock->restartClock();
}

void Weaponspawner::leerSpawnerPosition() {
    spawnArmas = Partida::getInstance()->mapa->getSpawnArmas();
}

void Weaponspawner::leerArmas() {

    const char *cstr = weaponFile.c_str();
    TiXmlDocument doc(cstr);
    doc.LoadFile();

    TiXmlElement* armas = doc.FirstChildElement("armas");
    TiXmlElement* arma = armas->FirstChildElement("arma");

    int i = 0;

    while (arma) {
        datosArma nuevosDatos;
        nuevosDatos.indice = i;

        arma->QueryIntAttribute("bpd", &nuevosDatos.bpd);
        arma->QueryIntAttribute("cargador", &nuevosDatos.cargador);
        arma->QueryIntAttribute("rareza", &nuevosDatos.rareza);
        arma->QueryIntAttribute("recoil", &nuevosDatos.recoil);
        arma->QueryIntAttribute("rango", &nuevosDatos.rango);
        arma->QueryFloatAttribute("recoiltime", &nuevosDatos.recoiltime);
        arma->QueryBoolAttribute("parabola", &nuevosDatos.parabola);
        arma->QueryBoolAttribute("explosivo", &nuevosDatos.explosivo);

        TiXmlElement* rect = arma->FirstChildElement();
        rect->QueryFloatAttribute("x", &nuevosDatos.rectangulo.x);
        rect->QueryFloatAttribute("y", &nuevosDatos.rectangulo.y);
        rect->QueryFloatAttribute("w", &nuevosDatos.rectangulo.w);
        rect->QueryFloatAttribute("h", &nuevosDatos.rectangulo.h);

        datosArmas.push_back(nuevosDatos);
        arma = arma->NextSiblingElement("arma");
        i++;
    }
}

void Weaponspawner::Update() {
    currentTime = currentTime - clock->getDeltaTimeAsSeconds();
    clock->restartClock();

    if (currentTime <= 0) {
        currentTime = respawnTime;
        deleteNotUsedWeapon();
        cargarArmas();
    }
}

void Weaponspawner::cargarArmas() {
    srand(time(NULL));
    for (int i = 0; i < spawnArmas.size(); i++) {

        datosArma datos;
        int grupo = -1;
        int indice = rand() % 20; //100% (0 a 19)

        if (indice <= 8) grupo = 0; //40%
        else if (indice <= 15) grupo = 1; //35%
        else if (indice <= 19) grupo = 2; //25%

        do {
            indice = rand() % datosArmas.size();
            datos = datosArmas.at(indice);
        } while (grupo != datos.rareza);

        vector<int> spawn = spawnArmas.at(i);
        float x = spawn.at(0);
        float y = spawn.at(1);

        Weapon* arma = new Weapon(datos.rectangulo.w * 0.65, datos.rectangulo.h * 0.65, x, y, datos.recoiltime, datos.bpd, datos.cargador, datos.recoil, datos.rango, datos.parabola, datos.explosivo);
        arma->m_vBody->setRect(datos.rectangulo.x, datos.rectangulo.y, datos.rectangulo.w, datos.rectangulo.h);
        Partida::getInstance()->worldWeapons.push_back(arma);
    }
}

void Weaponspawner::cargarArmas(int indice) {
    if (indice >= 0 && indice < datosArmas.size()) {
        deleteNotPossessedWeapons();
        for (int i = 0; i < spawnArmas.size(); i++) {
            datosArma datos = datosArmas.at(indice);

            vector<int> spawn = spawnArmas.at(i);
            float x = spawn.at(0);
            float y = spawn.at(1);

            Weapon* arma = new Weapon(datos.rectangulo.w * 0.65, datos.rectangulo.h * 0.65, x, y, datos.recoiltime, datos.bpd, datos.cargador, datos.recoil, datos.rango, datos.parabola, datos.explosivo);
            arma->m_vBody->setRect(datos.rectangulo.x, datos.rectangulo.y, datos.rectangulo.w, datos.rectangulo.h);
            Partida::getInstance()->worldWeapons.push_back(arma);
        }
    }
}

void Weaponspawner::deleteNotUsedWeapon() {
    for (int i = 0; i < Partida::getInstance()->worldWeapons.size(); i++) {
        Weapon* arma = Partida::getInstance()->worldWeapons.at(i);
        if (arma != NULL) {
            if (!arma->used) {
                Partida::getInstance()->weapons2Delete.push_back(Partida::getInstance()->worldWeapons.at(i));
                Partida::getInstance()->worldWeapons.at(i) = NULL;
            }
        }
    }
}

void Weaponspawner::deleteNotPossessedWeapons() {
    for (int i = 0; i < Partida::getInstance()->worldWeapons.size(); i++) {
        Weapon* arma = Partida::getInstance()->worldWeapons.at(i);
        if (arma != NULL) {
            if (!arma->inPossession) {
                Partida::getInstance()->weapons2Delete.push_back(Partida::getInstance()->worldWeapons.at(i));
                Partida::getInstance()->worldWeapons.at(i) = NULL;
            }
        }
    }
}

Weaponspawner::~Weaponspawner() {
    deleteNotPossessedWeapons();
}

