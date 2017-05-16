
/* 
 * File:   Hud.h
 * Author: pedro
 *
 * Created on 30 de abril de 2017, 13:35
 */

#ifndef HUD_H
#define HUD_H

#include "../motorgrafico/headerfiles/Texto.h"
#include "Player.h"

using namespace std;

class Hud {
public:

    /*
     * Devuelve la instancia de Hud, si no existe crea un Hud
     */
    static Hud* getInstance();

    /*
     * Funcion que actualiza el hud
     */
    void update();

    /*
     *Funcion que dibuja el hud 
     */
    void render();

    /*
     * Funcion que añade jugadores al vector de jugadores
     */
    void addPlayer(Player* p);

    /*
     * Funcion que elimina jugadores del vector de jugadores
     */
    void deletePlayers();

    virtual ~Hud();
    
private:
    int screenW, screenH;
    std::vector<Player*> players;
    std::vector< std::vector<int> > positions;
    std::vector<VisibleBody*> avatars;
    std::vector<VisibleBody*> weaponsIcon;
    std::vector<VisibleBody*> crosses;
    std::vector<Texto*> ammos;
    
    /*
     * Constructor de hud
     * @param std::vector<Player> j: Vector de jugadores en partida
     * @param int w: Ancho de la pantalla
     * @param int h: Altura de la pantalla
     */
    Hud();

};

#endif /* HUD_H */

