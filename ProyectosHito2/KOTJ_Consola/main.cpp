#include <iostream>
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "headerfiles/Partida.h"

using namespace std;

int main() {
    Partida *partida = Partida::getInstance();
    partida->loadMap();
    
    while(partida->window->isOpen()){
        partida->Input();
        partida->Update();
        partida->Erase();
        partida->Render();
    }
    
    return 0;
}