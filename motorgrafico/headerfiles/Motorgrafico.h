
/* 
 * File:   Motorgrafico.h
 * Author: amygwyllion
 *
 * Created on 11 de abril de 2017, 20:17
 */


#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include "../../headerfiles/Partida.h"
#include "../../headerfiles/Menu.h"
#include "Animation.h"
#include "SpriteAnimated.h"
#include "Temporizador.h"
#include "musicPlayer.h"

class Motorgrafico {
public:
    static Motorgrafico* getInstance();

    void createPartida(int tiempo);
    Partida* getPartida();
    void deletePartida();

    void setFramerateLimitOn(int framerate);
    void setMainCameraView();
    void setHudCameraView();
    void cameraSetFinalTransform();
    void lerpCameraTransform();

    void clearWindow();
    void eventListener(int &estado);
    void eventListener(int &estado, Menu* menu);
    void updateWindow();
    void displayWindow();

    sf::RenderWindow *getRenderWindow();

    void updateTemporizador();
    void drawTemporizador();

    void resetFrameTime();
    sf::Time getFrameTime();

    void createMusicPlayer();
    MusicPlayer* getMusicPlayer();

    template <class T1> void draw(T1&);
    void draw(SpriteAnimated&);
    void draw(sf::RectangleShape);
    void draw(sf::RectangleShape&);
    void draw(sf::CircleShape);
    void draw(Sprite&);
    void draw(sf::Text);

    float getCameraPositionX();
    float getCameraPositionY();
    int getWindowHeight();
    int getWindowWidth();
    void renderizarInstrucciones();
    void renderizarInstrucciones2();

    Temporizador* getTemporizador();

    void setGoToMenu(bool go);
    
    void textEnteredConsole(Event even);
    virtual ~Motorgrafico();

private:
    Motorgrafico();

    Partida *partida;

    Temporizador *temporizador;
    sf::Clock frameClock;
    sf::Time frameTime;

    Vector2f finalCameraPosition;
    Vector2f finalCameraSize;
    float cameraVelocity;

    sf::RenderWindow *window;
    sf::View *mainCamera;
    sf::View *hudCamera;
    sf::Event event;
    MusicPlayer *mplayer;
    
    Fondo *fondoMenu;
    Fondo *mando;
    Fondo *teclado;
    Texto *texto;
    int contControles;

    bool goToMenuNow;
};

