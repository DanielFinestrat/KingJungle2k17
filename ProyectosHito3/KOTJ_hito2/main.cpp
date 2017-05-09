
#include "headerfiles/Partida.h"
#include "motorgrafico/headerfiles/Texto.h"
#include "motorgrafico/headerfiles/Motorgrafico.h"
#include "motorgrafico/headerfiles/musicPlayer.h"

using namespace std;

int state;

Menu* createMainMenu() {
    Texto* op1 = new Texto("Jugar", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op2 = new Texto("Opciones de partida", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op3 = new Texto("Opciones del juego", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op4 = new Texto("Salir", 18, "./resources/fonts/bits.ttf", 255, 0, 0);

    std::vector<Texto*> vec(4);
    vec[0] = op1;
    vec[1] = op2;
    vec[2] = op3;
    vec[3] = op4;

    Menu* menu = new Menu(vec, 512, 250);
    return menu;
}

Menu* createGameMenu() {
    Texto* op1 = new Texto("Rondas", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op2 = new Texto("Tiempo", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op3 = new Texto("Modo", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op4 = new Texto("Volver", 18, "./resources/fonts/bits.ttf", 255, 0, 0);

    std::vector<Texto*> vec(4);
    vec[0] = op1;
    vec[1] = op2;
    vec[2] = op3;
    vec[3] = op4;

    Menu* menu = new Menu(vec, 512, 250, 5, 20, 1);

    return menu;
}

Menu* createOptions() {
    Texto* op1 = new Texto("1: Musica +", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op2 = new Texto("2: Musica -", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op3 = new Texto("3: SFX +", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op4 = new Texto("4: SFX -", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op5 = new Texto("5: Volver", 18, "./resources/fonts/bits.ttf", 255, 0, 0);

    std::vector<Texto*> vec(5);
    vec[0] = op1;
    vec[1] = op2;
    vec[2] = op3;
    vec[3] = op4;
    vec[4] = op5;

    Menu* menu = new Menu(vec, 512, 250);
    return menu;
}

Menu* createPause() {
    Texto* op1 = new Texto("1: Reanudar", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op2 = new Texto("2: Volver al menu", 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    Texto* op3 = new Texto("3: Salir del juego", 18, "./resources/fonts/bits.ttf", 255, 0, 0);

    std::vector<Texto*> vec(3);
    vec[0] = op1;
    vec[1] = op2;
    vec[2] = op3;

    Menu* menu = new Menu(vec, 512, 250);
    return menu;
}

int main() {
    bool empezada = false;
    state = 1;
    Menu* menu;
    Motorgrafico *mg = Motorgrafico::getInstance();

    Fondo* fondoCarga = new Fondo("./resources/fondos/fondoCarga.png", true);
    fondoCarga->Update();
    fondoCarga->Render();

    mg->createMusicPlayer();
    mg->getMusicPlayer()->playSound(mg->getMusicPlayer()->menuMusic);

    while (state != 0) {

        if (state == 1) {
            empezada = false;
            menu = createMainMenu();

            mg->getMusicPlayer()->setLoop(mg->getMusicPlayer()->menuMusic);

            //->isOpen() es un método de sfml, creo que deberiamos crear un método en el motorgrafico que haga totalmente lo mismo
            while (mg->getRenderWindow()->isOpen() && state == 1) {
                menu->input(state, menu);
                menu->update();
                menu->render();
            }

            menu = NULL;
        }

        if (state == 2) {
            if (!empezada) {
                Motorgrafico::getInstance()->createPartida();
                Motorgrafico::getInstance()->getPartida()->loadMap("./resources/mapas/mapaSeleccion.tmx");
                empezada = true;
            }
            mg->getMusicPlayer()->stopSound(mg->getMusicPlayer()->menuMusic);

            if (Partida::getInstance()->mapa->getIfFirstMap()) {
                mg->getMusicPlayer()->playSound(mg->getMusicPlayer()->elevatorMusic);
                mg->getMusicPlayer()->setLoop(mg->getMusicPlayer()->elevatorMusic);
            } else {
                mg->getMusicPlayer()->playSound(mg->getMusicPlayer()->battleMusic);
                mg->getMusicPlayer()->setLoop(mg->getMusicPlayer()->battleMusic);
            }

            while (mg->getRenderWindow()->isOpen() && state == 2) {
                Motorgrafico::getInstance()->getPartida()->Input(state);
                Motorgrafico::getInstance()->getPartida()->Update();
                Motorgrafico::getInstance()->getPartida()->Erase();
                Motorgrafico::getInstance()->getPartida()->Render();
            }

            mg->getMusicPlayer()->stopSound(mg->getMusicPlayer()->battleMusic);
            mg->getMusicPlayer()->stopSound(mg->getMusicPlayer()->elevatorMusic);

            //Motorgrafico::getInstance()->deletePartida();
        }


        if (state == 3) {

            menu = createGameMenu();

            int i = 0;
            while (mg->getRenderWindow()->isOpen() && state == 3) {
                i++;
                menu->input(state, menu);
                menu->gameUpdate();
                menu->renderGameMenu();
            }

            menu = NULL;
        }

        if (state == 4) {
            menu = createOptions();

            while (mg->getRenderWindow()->isOpen() && state == 4) {
                menu->input(state, menu);
                menu->update();
                menu->render();
            }
            menu = NULL;
        }

        if (state == 5) {
            Menu* pauseMenu = createPause();
            while (Motorgrafico::getInstance()->getRenderWindow()->isOpen() && state == 5) {
                pauseMenu->input(state, pauseMenu);
                pauseMenu->update();
                pauseMenu->render();
            }
            pauseMenu = NULL;
        }
    }

    mg = NULL;
    delete mg;
    delete menu;
    return 0;
}