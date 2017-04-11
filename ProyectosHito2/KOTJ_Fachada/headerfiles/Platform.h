/* 
 * File:   Platform.h
 * Author: daniel
 *
 * Created on 26 de marzo de 2017, 14:03
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include "../Box2D/Box2D.h"
#include <vector>
#include "Entidad.h"
#include "../motorfisico/headerfiles/Cuerpo.h"
#include "../motorfisico/headerfiles/Motorfisico.h"
using namespace std;

class Platform : public Entidad {
public:

    Cuerpo *cuerpo;
    sf::RectangleShape *shape;

    Platform();
    Platform(const Platform& orig);
    Platform(float sizex, float sizey, float posx, float posy, float friction);

    void Render(sf::RenderWindow *window);

    virtual ~Platform();
private:

};

#endif /* PLATFORM_H */