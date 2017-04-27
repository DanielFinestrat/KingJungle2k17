#include "headerfiles/Partida.h"
#include "motorgrafico/headerfiles/Motorgrafico.h"

using namespace std;

int main() {
    Motorgrafico *mg = Motorgrafico::getInstance();
    
    Partida *partida = Partida::getInstance();
    partida->loadMap();
    
    while(mg->getRenderWindow()->isOpen()){
        partida->Input();
        partida->Update();
        partida->Erase();
        partida->Render();
    }
    
    return 0;
}