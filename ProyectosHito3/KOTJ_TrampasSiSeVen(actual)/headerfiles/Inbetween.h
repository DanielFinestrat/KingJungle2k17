
/* 
 * File:   Inbetween.h
 * Author: danielfinestrat
 *
 * Created on 16 de mayo de 2017, 19:43
 */

#ifndef INBETWEEN_H
#define INBETWEEN_H

#include <vector>
#include <sstream>
#include "../motorgrafico/headerfiles/VisibleBody.h"
#include "../motorgrafico/headerfiles/resources.h"
#include "../motorgrafico/headerfiles/Fondo.h"

using namespace std;

class Inbetween {
public:
    Inbetween(vector<Player*> jugadores);
    void Update();
    void render();
    void renderCrowns();
    void renderFaces();
    void renderPunt();
    virtual ~Inbetween();

private:
    vector<VisibleBody*> playerVB;
    vector<VisibleBody*> coronaVB;
    vector<Texto*> puntuacionText;
    vector<int> puntuacion;
    Fondo* fondo;

};

#endif /* INBETWEEN_H */

