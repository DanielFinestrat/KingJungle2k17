
#include "headerfiles/Partida.h"
#include "motorgrafico/headerfiles/Texto.h"
#include "motorgrafico/headerfiles/Motorgrafico.h"
#include "motorgrafico/headerfiles/musicPlayer.h"
int state;
using namespace std;

Menu* createMenu() {
    Texto* op1 = new Texto("1: Jugar", 18,"./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op2 = new Texto("2: Salir", 18,"./resources/fonts/bits.ttf", 255, 0, 0);
    
    std::vector<Texto*> vec(2);
    vec[0] = op1;    
    vec[1] = op2;
    
    Menu* menu = new Menu(vec, 512, 250);
    return menu;
}

int main() {
    state = 1;
    Menu* menu;
    Motorgrafico *mg = Motorgrafico::getInstance();
    mg->createMusicPlayer();
    
    while (state != 0) {
        
        if(state == 1) {
            menu = createMenu();
            
            mg->getMusicPlayer()->playSound(mg->getMusicPlayer()->menuMusic);
            mg->getMusicPlayer()->setLoop(mg->getMusicPlayer()->menuMusic);
            mg->getMusicPlayer()->setVolume(mg->getMusicPlayer()->menuMusic,50);
            
            while(mg->getRenderWindow()->isOpen() && state == 1) {
                menu->input(state, menu);
                menu->update();
                menu->render();
            }
            
            mg->getMusicPlayer()->stopSound(mg->getMusicPlayer()->menuMusic);
            
            menu = NULL;            
        }
                
        if(state == 2) {
            Partida *partida = Partida::getInstance();

            partida->loadMap();
            
            mg->getMusicPlayer()->playSound(mg->getMusicPlayer()->battleMusic);
            mg->getMusicPlayer()->setLoop(mg->getMusicPlayer()->battleMusic);
            mg->getMusicPlayer()->setVolume(mg->getMusicPlayer()->battleMusic,50);

            while(mg->getRenderWindow()->isOpen() && state == 2){
                partida->Input(state);
                partida->Update();
                partida->Erase();
                partida->Render();      
            }
            
            mg->getMusicPlayer()->stopSound(mg->getMusicPlayer()->battleMusic);
            
            partida = NULL;
            delete partida;
            
        }
    }
    
    delete mg;
    delete menu;
    return 0;
}