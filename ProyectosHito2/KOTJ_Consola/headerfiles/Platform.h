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
using namespace std;

class Platform: public Entidad {
public:
    
    b2Body *body;
    sf::RectangleShape *shape;
    
    Platform();
    Platform(const Platform& orig);
    
    /**
     * Crea una plataforma
     * @param world -- el mundo donde se crea
     * @param position -- la posicion en pixeles
     * @param size -- el tamaño en pixeles
     */
    Platform(b2World *world, sf::Vector2f size, sf::Vector2f position, float friction);
    
    void Render(sf::RenderWindow *window);
    
    virtual ~Platform();
private:

};

#endif /* PLATFORM_H */

