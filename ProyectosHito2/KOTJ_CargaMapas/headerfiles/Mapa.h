
/* 
 * File:   Mapa.h
 * Author: danielfinestrat
 *
 * Created on 28 de abril de 2017, 10:42
 */

#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include "../headerfiles/Platform.h"
#include "../tinyxml/headerfiles/tinystr.h"
#include "../tinyxml/headerfiles/tinyxml.h"
#include "../motorgrafico/headerfiles/VisibleBody.h"

using namespace std;

class Mapa {
public:

    const string mapaPrueba = "./resources/mapas/mapaPrueba.tmx";
    const string mapaSelva = "./resources/mapas/mapaSelva.tmx";
    
    Mapa();
    virtual ~Mapa();

    void leerMapa(string mapa);
    void cargarXML();
    void cargarTiles(int y, int x);
    void guardarCapas(TiXmlElement* map);
    void guardarObj(TiXmlElement* map);
    
    vector< vector<int> > getEsquinas();
    vector< vector<int> > getSpawnArmas();
    
    void drawMap();
    
private:
    string fondo;
    int ***_tilemap;
    
    vector<VisibleBody*> map_sprites;
    vector< vector<int> > spawnPlayer;
    vector< vector<int> > spawnArmas;
    vector< vector<int> > esquinasMapa;
    vector<Platform*> worldPlatforms;
    
};

#endif /* CARGAMAPAS_H */

