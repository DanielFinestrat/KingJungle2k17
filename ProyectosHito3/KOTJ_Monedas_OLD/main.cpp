
#include "headerfiles/Partida.h"
#include "motorgrafico/headerfiles/Texto.h"
#include "motorgrafico/headerfiles/Motorgrafico.h"
#include "motorgrafico/headerfiles/musicPlayer.h"

using namespace std;

int state;

Menu* createMainMenu() {
    Texto* op1 = new Texto("Jugar", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    Texto* op2 = new Texto("Opciones de partida", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    Texto* op3 = new Texto("Opciones del sonido", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    Texto* op4 = new Texto("Salir", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);

    std::vector<Texto*> vec(4);
    vec[0] = op1;
    vec[1] = op2;
    vec[2] = op3;
    vec[3] = op4;

    Menu* menu = new Menu(vec, 350, 200);
    return menu;
}

Menu* createGameMenu(int rondas, int tiempo, int modo) {
    Texto* op1 = new Texto("Puntos", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    Texto* op2 = new Texto("Tiempo", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    Texto* op3 = new Texto("Modo", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    Texto* op4 = new Texto("Volver", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);

    std::vector<Texto*> vec(4);
    vec[0] = op1;
    vec[1] = op2;
    vec[2] = op3;
    vec[3] = op4;

    Menu* menu = new Menu(vec, 350, 200, rondas, tiempo, modo);

    return menu;
}

Menu* createOptionsMenu() {
    Texto* op1 = new Texto("Volumen de musica", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    Texto* op2 = new Texto("Volumen de efectos", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    Texto* op3 = new Texto("Volver", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);

    std::vector<Texto*> vec(3);
    vec[0] = op1;
    vec[1] = op2;
    vec[2] = op3;

    int vm = Motorgrafico::getInstance()->getMusicPlayer()->getMusicVolume();
    int vfx = Motorgrafico::getInstance()->getMusicPlayer()->getSFXVolume();
    Menu* menu = new Menu(vec, 350, 200, vm, vfx);
    return menu;
}

Menu* createPause() {
    Texto* op1 = new Texto("Reanudar", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    Texto* op2 = new Texto("Volver al menu", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    Texto* op3 = new Texto("Salir del juego", 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);

    std::vector<Texto*> vec(3);
    vec[0] = op1;
    vec[1] = op2;
    vec[2] = op3;

    Menu* menu = new Menu(vec, 350, 200);
    return menu;
}

int main() {
    bool empezada = false;

    state = 1;
    Menu* menu;
    Motorgrafico *mg = Motorgrafico::getInstance();
    Fondo* fondo = new Fondo("./resources/fondos/fondoCarga.png", true);
    fondo->Update();
    fondo->Render();
    mg->createMusicPlayer();
    mg->getMusicPlayer()->playSound(mg->getMusicPlayer()->menuMusic);

    //datos Basicos de la partida
    vector<int> datosPartida; //int puntos tiempo modo
    datosPartida.push_back(5);
    datosPartida.push_back(60);
    datosPartida.push_back(1);

    while (state != 0) {

        if (state == 1) {
            if (empezada) {
                Partida::getInstance()->worldPlayer.clear();
                Partida::getInstance()->worldControlador.clear();
                Motorgrafico::getInstance()->setGoToMenu(false);
                Partida::getInstance()->lastLevel = false;
                Partida::getInstance()->gameisover = false;
                Partida::getInstance()->setUsingKeyboard(false);
            }

            empezada = false;
            Motorgrafico::getInstance()->setGoToMenu(false);

            menu = createMainMenu();
            mg->getMusicPlayer()->setLoop(mg->getMusicPlayer()->menuMusic);

            while (mg->getRenderWindow()->isOpen() && state == 1) {
                menu->input(state, menu);
                menu->update();
                menu->render();
            }

            menu = NULL;
        }

        if (state == 2) {
            if (!empezada) {
                Partida* partida;
                Motorgrafico::getInstance()->createPartida(datosPartida.at(1));
                partida = Motorgrafico::getInstance()->getPartida();
                partida->indexMap = -1;
                Partida::getInstance()->setMaxPoints(datosPartida.at(0));
                Partida::getInstance()->fillRondasVector(datosPartida.at(2));
                partida->loadMap("./resources/mapas/mapaSeleccion.tmx");
                Partida::getInstance()->checkJoysticksConnected();
                empezada = true;
            }

            mg->getMusicPlayer()->stopSound(mg->getMusicPlayer()->menuMusic);

            if (Motorgrafico::getInstance()->getPartida()->mapa->getIfFirstMap()) {
                mg->getMusicPlayer()->playSound(mg->getMusicPlayer()->elevatorMusic);
                mg->getMusicPlayer()->setLoop(mg->getMusicPlayer()->elevatorMusic);
            } else {
                mg->getMusicPlayer()->playSound(mg->getMusicPlayer()->battleMusic);
                mg->getMusicPlayer()->setLoop(mg->getMusicPlayer()->battleMusic);
            }

            while (mg->getRenderWindow()->isOpen() && state == 2) {
                mg->getPartida()->Input(state);
                if (mg->getPartida()->getInstance()->loadingLevelStruct.loadingLevel) {
                    mg->getPartida()->updateBeforeMap();
                } else if (mg->getPartida()->getInstance()->loadingLevelStruct.showingInbetween) {
                    mg->getPartida()->inbetweenUpdate();
                } else {
                    mg->getPartida()->Update();
                }
                mg->getPartida()->Erase();
                mg->getPartida()->Render();

            }

            mg->getMusicPlayer()->stopSound(mg->getMusicPlayer()->battleMusic);
            mg->getMusicPlayer()->stopSound(mg->getMusicPlayer()->elevatorMusic);
        }


        if (state == 3) {

            menu = createGameMenu(datosPartida.at(0), datosPartida.at(1), datosPartida.at(2));

            while (mg->getRenderWindow()->isOpen() && state == 3) {
                menu->input(state, menu);
                menu->gameUpdate();
                menu->renderGameMenu();
            }

            datosPartida.at(0) = menu->getPuntos();
            datosPartida.at(1) = menu->getTiempo();
            datosPartida.at(2) = menu->getMode();

            menu = NULL;
        }

        if (state == 4) {
            menu = createOptionsMenu();

            while (mg->getRenderWindow()->isOpen() && state == 4) {
                menu->input(state, menu);
                menu->optionsUpdate();
                menu->renderOptionsMenu();
            }
            menu = NULL;
        }

        if (state == 5) {
            Partida::getInstance()->worldWeapons.clear();
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