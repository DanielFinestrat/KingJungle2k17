#include <SFML/Graphics.hpp>
#include "headerfiles/Partida.h"
#include "headerfiles/Menu.h"

using namespace std;
int state;

void setState(int i) {
    state = i;
}

Menu* createMenu() {
    Texto* op1 = new Texto("1: Jugar", 18,"./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op2 = new Texto("2: Salir", 18,"./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op3 = new Texto("2: Salir", 18,"./resources/fonts/bits.ttf", 0, 0, 255);
    
    std::vector<Texto*> vec(3);
    vec[0] = op1;    
    vec[1] = op2;
    vec[2] = op3;
    
    Menu* menu = new Menu(vec, 512, 250);
    return menu;
}

int main() {
    Menu* menu;
    state = 1;
    while(state == 1 || state == 2) {
        
    
        switch(state) {
            case(1):

                menu = createMenu();

                while(menu->window->isOpen()&& state == 1) {

                    //ESTO DEBERIA IR EN LA CLASE MENU EN UN FUTURO, CON JUEGO CREADO
                    // menu->input();
                    
                    sf::Event event;
                    while (menu->window->pollEvent(event)) {
                        switch (event.type) {
                            case Event::Closed:
                                state = 3;
                                menu->window->close();
                                break;

                            case Event::JoystickMoved:
                                if(event.joystickMove.axis == Joystick::Y) {
                                    if(event.joystickMove.position > 10) { menu->goUp(); }

                                    if(event.joystickMove.position < -10) { menu->goDown(); }
                                }
                                break;

                            case Event::KeyPressed:
                                switch(event.key.code) {
                                    case Keyboard::Down:
                                        menu->goDown();
                                        std::cout << "tecla abajo" << std::endl;
                                        break;

                                    case Keyboard::Up:
                                        menu->goUp();
                                        std::cout << "tecla arriba" << std::endl;
                                        break;
                                }
                                break;

                            case Event::KeyReleased: 

                                if(event.key.code == 58) {
                                    std::cout << "He pulsado intro" << std::endl;
                                    if(menu->getCurrentOption() == 0) state = 2; else state = 3;
                                }
                        }
                    }
                    //---------------------------------------------------------------------------
                    menu->update();
                    menu->render();
                }

                std::cout << "estado: " << state << std::endl;
                break;

            case(2):
                Partida *partida = Partida::getInstance();  
                partida->loadMap();

                while(partida->window->isOpen()){
                    partida->Input();
                    partida->Update();
                    partida->Erase();
                    partida->Render();
                }
                state = 1;

                break;
        }
    }
    
    return 0;
}