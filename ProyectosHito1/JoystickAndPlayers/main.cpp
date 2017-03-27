#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include "Box2D/Box2D.h"
#include "PlayerJoystick.h"

#define screenWidth 800
#define screenHeight 600

#define TIMESTEP 1.0f/15.f      //TIEMPO DE REFRESCO
#define VELITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA POSICION

#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

using namespace std;
using namespace sf;

//Nos da el indice en el vector del mando con la id pasada (-1 si no existe))
int findJoystickWithId(vector<PlayerJoystick> *playerJoysticks, int id){
    int index = -1;
    
    for(int i = 0; i < playerJoysticks->size() && index == -1; i++){
        if(playerJoysticks->at(i).id == id) index = i;
    }
    
    return index;
}

//Añade un jugador con la id indicada (Si no existe ya))
void addPlayerJoystick(vector<PlayerJoystick> *playerJoysticks, int id, b2World *world){
    //Para saber si la tenemos que añador
    bool add = true;
    
    //Comprobamos si existe el mando y actualizamos la condición
    for(int i = 0; i < playerJoysticks->size() && add; i++){
        if(playerJoysticks->at(i).id-1 == i) add = false;
    }
    
    //Añadimos en funcion de la condición
    if (add){
        PlayerJoystick p(id, world);
        playerJoysticks->push_back(p);
    }

}

void updatePlayers(Time frameTime, vector<PlayerJoystick> *playerJoysticks){
    for(int i = 0; i < playerJoysticks->size(); i++){
        playerJoysticks->at(i).player->update(frameTime);
    }
}

void drawPlayers(RenderWindow *Ventana, vector<PlayerJoystick> *playerJoysticks){
    for(int i = 0; i < playerJoysticks->size(); i++){
        Ventana->draw(playerJoysticks->at(i).player->getPlayerSprite());
    }
}

int main() {    
    RenderWindow Ventana(VideoMode(screenWidth, screenHeight),"Clase Joystick + Personajes");
    Ventana.setFramerateLimit(60);
    
    //Necesario para la crear un Joystick-Jugador
    b2World world(b2Vec2(0.0f, 9.8f));
    
    //Creamos el manager y el vector de Joysticks-Jugadores
    Joystick joystickManager;
    vector<PlayerJoystick> playerJoysticks;
    
    //reloj con el que cambiaran los frames de la animacion
    Clock frameClock;
            
    //Definir Suelo Box2D y SFML
    b2BodyDef sueloBodyDef;
    sueloBodyDef.position.Set(screenWidth/2*MPP, 550.0f*MPP);
    b2Body* sueloBody = world.CreateBody(&sueloBodyDef);
    b2PolygonShape sueloBox;
    sueloBox.SetAsBox(800.0f/2*MPP, 100.0f/2*MPP);
    sueloBody->CreateFixture(&sueloBox, 0.0f);

    RectangleShape rectSuelo(Vector2f(screenWidth, 100));
    rectSuelo.setOrigin(screenWidth/2, 100/2);
    rectSuelo.setPosition(Vector2f(sueloBody->GetPosition().x*PPM, sueloBody->GetPosition().y * PPM));
    rectSuelo.setFillColor(Color::Blue);

    //Definir Techo Box2D y SFML
    b2BodyDef techoBodyDef;
    techoBodyDef.position.Set(screenWidth/4*MPP, 350.0f*MPP);
    b2Body* techoBody = world.CreateBody(&techoBodyDef);
    b2PolygonShape techoBox;
    techoBox.SetAsBox(800.0f/2*MPP, 100.0f/2*MPP);
    techoBody->CreateFixture(&sueloBox, 0.0f);

    RectangleShape rectTecho(Vector2f(screenWidth, 100));
    rectTecho.setOrigin(screenWidth/2, 100/2);
    rectTecho.setPosition(Vector2f(techoBody->GetPosition().x*PPM, techoBody->GetPosition().y * PPM));
    rectTecho.setFillColor(Color::Red);
    
    //Creamos los iniciales (Hasta 4)
    for(int i = 0; i < 4; i++){
        if(joystickManager.isConnected(i)){
            addPlayerJoystick(&playerJoysticks, i, &world);
        }
    }
    
    while(Ventana.isOpen()){
        
        //reseteamos el tiempo de los frames
        Time frameTime = frameClock.restart();
        world.Step(TIMESTEP, VELITER, POSITER);
        
        Event event;
        while (Ventana.pollEvent(event)) {
            switch (event.type) {
                
                case Event::Closed:
                    Ventana.close();
                    break;
                
                case Event::JoystickConnected:
                    addPlayerJoystick(&playerJoysticks, event.joystickConnect.joystickId, &world);
                    break;
                    
                case Event::JoystickMoved:
                    if(event.joystickMove.axis == Joystick::X){
                        playerJoysticks.at(findJoystickWithId(&playerJoysticks, event.joystickMove.joystickId)).checkAxisX(event.joystickMove.position);
                    }
                    if(event.joystickMove.axis == Joystick::Y){
                        playerJoysticks.at(findJoystickWithId(&playerJoysticks, event.joystickMove.joystickId)).checkAxisY(event.joystickMove.position);
                    }
                    break;
                    
                case Event::JoystickButtonPressed:
                    playerJoysticks.at(findJoystickWithId(&playerJoysticks, event.joystickButton.joystickId)).pressUpdateState(event.joystickButton.button);
                    break;
                    
                case Event::JoystickButtonReleased:
                    playerJoysticks.at(findJoystickWithId(&playerJoysticks, event.joystickButton.joystickId)).releaseUpdateState(event.joystickButton.button);
                    break;
            }
        }
        
        updatePlayers(frameTime, &playerJoysticks);
                
        Ventana.clear(Color::Black);
        drawPlayers(&Ventana, &playerJoysticks);
        Ventana.draw(rectSuelo);
        Ventana.draw(rectTecho);
        Ventana.display();
    }
        

    return 0;
}