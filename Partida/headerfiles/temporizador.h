/* 
 * File:   temporizador.h
 * Author: daniel
 *
 * Created on 27 de marzo de 2017, 13:05
 */

#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

#include <SFML/Graphics.hpp>
#include "../Box2D/Box2D.h"

using namespace std;

class temporizador : public sf::Drawable, public sf::Transformable {
public:
    temporizador();
    temporizador(int time);
    temporizador(const temporizador& orig);
    
    void Update();
    void changeRemainingTime();
    float getRemainingTime();
    
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    virtual ~temporizador();
private:
    
    sf::Clock chrono;
    sf::Font font;

};

#endif /* TEMPORIZADOR_H */

