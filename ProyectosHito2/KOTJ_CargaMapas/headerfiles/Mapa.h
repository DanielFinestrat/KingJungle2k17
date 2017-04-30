
/* 
 * File:   Mapa.h
 * Author: danielfinestrat
 *
 * Created on 28 de abril de 2017, 10:42
 */

#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <string>
#include <cstdlib>
#include "../headerfiles/Platform.h"
#include "../tinyxml/headerfiles/tinystr.h"
#include "../tinyxml/headerfiles/tinyxml.h"
#include "../motorgrafico/headerfiles/VisibleBody.h"
#include "../motorgrafico/headerfiles/Fondo.h"

using namespace std;

class Mapa {
public:

    const string mapaPrueba = "./resources/mapas/mapaPrueba.tmx";
    const string mapaSelva = "./resources/mapas/mapaSelva.tmx";
    const string mapaCueva = "./resources/mapas/mapaCueva.tmx";
    const string mapaMar = "./resources/mapas/mapaMar.tmx";
    vector<string> mapas;
    
    Mapa();
    virtual ~Mapa();

    void Update();
    void leerMapa(string mapa);
    void cargarXML();
    void cargarTiles(int y, int x);
    void guardarFondo(TiXmlElement* map);
    void guardarCapas(TiXmlElement* map);
    void guardarObj(TiXmlElement* map);
   
    string getRandomMap();
    vector< vector<int> > getEsquinas();
    vector< vector<int> > getSpawnArmas();
    vector< vector<int> > getSpawnTrampas();
    
    void drawMap();
    void drawBackground();
    
private:
    string fondostr;
    Fondo* fondo;
    int ***_tilemap;
    
    vector<VisibleBody*> map_sprites;
    vector< vector<int> > spawnPlayer;
    vector< vector<int> > spawnArmas;
    vector< vector<int> > esquinasMapa;
    vector< vector<int> > spawnTrampas;
    vector<Platform*> worldPlatforms;
    
};

#endif /* MAPA_H */

