
/* 
 * File:   Fondo.h
 * Author: danielfinestrat
 *
 * Created on 29 de abril de 2017, 10:17
 */

#ifndef FONDO_H
#define FONDO_H

#include "../headerfiles/resources.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Fondo {
public:
    Fondo(string ruta, bool pantallaCarga);
    virtual ~Fondo();
    
    void Update();
    void setPosition(float x, float y);
    void Render();
    
private:
    Sprite* imagenFondo;
    bool pantallaCarga;
    
};

#endif /* FONDO_H */

