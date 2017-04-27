#include "headerfiles/Partida.h"
#include "motorgrafico/headerfiles/Texto.h"
#include "motorgrafico/headerfiles/Motorgrafico.h"
#include "motorgrafico/headerfiles/musicPlayer.h"
int state;
using namespace std;


    

Menu* createMenu() {
    Texto* op1 = new Texto("1: Jugar", 18,"./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op2 = new Texto("2: Salir", 18,"./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op3 = new Texto("3: Nada", 18,"./resources/fonts/bits.ttf", 0, 0, 255);
    
    std::vector<Texto*> vec(3);
    vec[0] = op1;    
    vec[1] = op2;
    vec[2] = op3;
    
    Menu* menu = new Menu(vec, 512, 250);
    return menu;
}

int main() {
    state = 1;
    Menu* menu;
    Motorgrafico *mg = Motorgrafico::getInstance();
    
    MusicPlayer *mplayer = new MusicPlayer();
    
    while (state != 0) {
        
        if(state == 1) {
            menu = createMenu();
            
            mplayer->playSound(mplayer->menuMusic);
            mplayer->setLoop(mplayer->menuMusic);
            mplayer->setVolume(mplayer->menuMusic,50);
            
            while(mg->getRenderWindow()->isOpen() && state == 1) {

                menu->input(state, menu);
                menu->update();
                menu->render();
            }
            
            mplayer->stopSound(mplayer->menuMusic);
            menu = NULL;
            
        }
                
        if(state == 2) {
            Partida *partida = Partida::getInstance();

            partida->loadMap();
            
            mplayer->playSound(mplayer->battleMusic);
            mplayer->setLoop(mplayer->battleMusic);
            mplayer->setVolume(mplayer->battleMusic,50);

            while(mg->getRenderWindow()->isOpen() && state == 2){
                partida->Input(state);
                partida->Update();
                partida->Erase();
                partida->Render();      
            }
            
            mplayer->stopSound(mplayer->battleMusic);
            partida = NULL;
            delete partida;
            
        }
        cout << state << endl;
    }
    
    mg = NULL;
    delete mg;
    delete menu;
    return 0;
}