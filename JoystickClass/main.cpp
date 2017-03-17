#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include "Box2D/Box2D.h"
#include "PlayerJoystick.h"

#define screenWidth 300
#define screenHeight 100

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
        if(playerJoysticks->at(i).id == i) add = false;
    }
    
    //Añadimos en funcion de la condición
    if (add){
        PlayerJoystick p(id, world);
        playerJoysticks->push_back(p);
    }

}

int main() {    
    RenderWindow Ventana(VideoMode(screenWidth, screenHeight),"Clase Joystick");
    Ventana.setFramerateLimit(60);
    
    //Necesario para la crear un Joystick-Jugador
    b2World world(b2Vec2(0.0f, 9.8f));
    
    //Creamos el manager y el vector de Joysticks-Jugadores
    Joystick joystickManager;
    vector<PlayerJoystick> playerJoysticks;
    
    //Creamos los iniciales (Hasta 4)
    for(int i = 0; i < 4; i++){
        if(joystickManager.isConnected(i)){
            addPlayerJoystick(&playerJoysticks, i, &world);
        }
    }
    
    while(Ventana.isOpen()){
        
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
        
        Ventana.clear(Color::Black);
        Ventana.display();
    }
        

    return 0;
}
