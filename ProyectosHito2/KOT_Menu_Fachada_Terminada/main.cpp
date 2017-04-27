#include "headerfiles/Partida.h"
#include "motorgrafico/headerfiles/Texto.h"
#include "motorgrafico/headerfiles/Motorgrafico.h"
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
    
    while (state != 0) {
        
        if(state == 1) {
            menu = createMenu();
            while(mg->getRenderWindow()->isOpen() && state == 1) {

                menu->input(state, menu);
                menu->update();
                menu->render();
            }
            
            menu = NULL;
        }
                
        if(state == 2) {
            Partida *partida = Partida::getInstance();

            partida->loadMap();

            while(mg->getRenderWindow()->isOpen() && state == 2){
                partida->Input(state);
                partida->Update();
                partida->Erase();
                partida->Render();      
            }
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