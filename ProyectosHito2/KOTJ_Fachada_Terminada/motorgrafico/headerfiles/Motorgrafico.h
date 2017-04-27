/* 
 * File:   Motorgrafico.h
 * Author: amygwyllion
 *
 * Created on 11 de abril de 2017, 20:17
 */


#include <SFML/Graphics.hpp>
#include "../../headerfiles/Partida.h"
#include "Animation.h"
#include "SpriteAnimated.h"
#include "Temporizador.h"


class Motorgrafico {
public:
    static Motorgrafico* getInstance();

    void setFramerateLimitOn(int framerate);
    void setMainCameraView();
    void setHudCameraView();
    void cameraSetTransform();
    
    void clearWindow();
    void eventListener();
    void updateWindow();
    void displayWindow();
    
    sf::RenderWindow *getRenderWindow();
        
    void updateTemporizador();
    void drawTemporizador();
    
    void resetFrameTime();
    sf::Time getFrameTime();
    
    template <class T1> void draw(T1&);
    void draw(SpriteAnimated&);
    void draw(sf::RectangleShape);
    void draw(sf::CircleShape);
    
    virtual ~Motorgrafico();
    
private:
    Motorgrafico();
    Motorgrafico(const Motorgrafico& orig);
    
    Partida *partida;
    
    Temporizador *temporizador;
    sf::Clock frameClock;
    sf::Time frameTime;
    
    sf::RenderWindow *window;
    sf::View *mainCamera;
    sf::View *hudCamera;
    sf::Event event;

};

