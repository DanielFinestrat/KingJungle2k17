
/* 
 * File:   Weaponspawner.cpp
 * Author: danielfinestrat
 * 
 * Created on 28 de abril de 2017, 19:23
 */

#include "../headerfiles/Weaponspawner.h"
#include "../headerfiles/Partida.h"
#include "../motorgrafico/headerfiles/Motorgrafico.h"

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
        arma->QueryFloatAttribute("recoiltime", &nuevosDatos.recoiltime);
        arma->QueryIntAttribute("rareza", &nuevosDatos.rareza);
        arma->QueryIntAttribute("rango", &nuevosDatos.rango);
        arma->QueryBoolAttribute("parabola", &nuevosDatos.parabola);
        arma->QueryIntAttribute("recoil", &nuevosDatos.recoil);
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
        checkIfUsed();
        cargarArmas();
    }
}

void Weaponspawner::Render(){
    for (int i = 0; i < armas.size(); i++) {
        if(armas.at(i) != NULL){
            Motorgrafico::getInstance()->draw(armas.at(i)->m_vBody->getShape());
        }
    }
}

void Weaponspawner::cargarArmas(int indice) {
    for (int i = 0; i < spawnArmas.size(); i++) {
        datosArma datos = datosArmas.at(indice);
        
        vector<int> spawn = spawnArmas.at(i);
        float x = spawn.at(0);
        float y = spawn.at(1);

        Weapon* arma = new Weapon(datos.rectangulo.w * 0.65, datos.rectangulo.h * 0.65, x, y, datos.recoiltime, datos.bpd, datos.cargador, datos.recoil, datos.parabola, datos.explosivo);
        arma->m_vBody->setRect(datos.rectangulo.x, datos.rectangulo.y, datos.rectangulo.w, datos.rectangulo.h);
        //armas.push_back(arma);
        Partida::getInstance()->worldWeapons.push_back(arma);
    }
}

void Weaponspawner::cargarArmas() {
    srand(time(NULL));
    for (int i = 0; i < spawnArmas.size(); i++) {

        int indice = -1;
        datosArma datos;
        
        do {
            indice = rand() % 20; //100% (0 a 19)
            
            if (indice <= 8) indice = 0; //40%
            else if (indice <= 15) indice = 1; //35%
            else if (indice <= 19) indice = 2; //25%
            
            datos = datosArmas.at(indice);
        } while (indice != datos.rareza);

        vector<int> spawn = spawnArmas.at(i);
        float x = spawn.at(0);
        float y = spawn.at(1);

        Weapon* arma = new Weapon(datos.rectangulo.w * 0.65, datos.rectangulo.h * 0.65, x, y, datos.recoiltime, datos.bpd, datos.cargador, datos.recoil, datos.parabola, datos.explosivo);
        arma->m_vBody->setRect(datos.rectangulo.x, datos.rectangulo.y, datos.rectangulo.w, datos.rectangulo.h);
        //armas.push_back(arma);
        Partida::getInstance()->worldWeapons.push_back(arma);
    }
}

void Weaponspawner::checkIfUsed() {
    for (int i = 0; i < armas.size(); i++) {
        if (armas.at(i) != NULL) {
            Weapon *arma = armas.at(i);
            if (arma->inPossession) {
                //Partida::getInstance()->worldWeapons.push_back(arma);
                //armas.at(i) == NULL;
            }
        }
    }
}

Weaponspawner::~Weaponspawner() {
}

