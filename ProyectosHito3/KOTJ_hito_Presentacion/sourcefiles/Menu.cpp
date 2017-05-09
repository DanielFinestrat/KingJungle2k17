
/* 
 * File:   Menu.cpp
 * Author: pedro
 * 
 * Created on 25 de abril de 2017, 14:27
 */

#include "../headerfiles/Menu.h"
#include "../motorgrafico/headerfiles/Motorgrafico.h"

Menu::Menu(std::vector<Texto*> op, int x, int y) {
    options = op;
    currentOpt = 0;
    posX = x;
    posY = y;

    fondo = new Fondo("./resources/fondos/fondomenu.png", false);

    puntero = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/puntero.png", true);

    int inc;
    for (int i = 0; i < options.size(); i++) {
        inc = i * 20;
        options[i]->setPos(posX, posY + inc);
    }
}

Menu::Menu(std::vector<Texto*> op, int x, int y, int r, float t, int m) {

    options = op;
    currentOpt = 0;
    posX = x;
    posY = y;

    rounds = r;
    time = t;
    mode = m;
    modes = std::vector<string>(3);
    modes[0] = "Normal";
    modes[1] = "Recolectar monedas";
    modes[2] = "Clavar la bandera";
    fondo = new Fondo("./resources/fondos/fondomenu.png", false);

    trounds = new Texto(rounds, 18, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    ttime = new Texto(time, 18, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    tmode = new Texto(modes[mode - 1], 18, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    puntero = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/puntero.png", true);
    puntero1 = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/puntero.png", true);
    puntero2 = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/puntero.png", true);

    int inc;
    for (int i = 0; i < options.size(); i++) {
        inc = i * 20;
        options[i]->setPos(posX, posY + inc);
    }
}

Menu::Menu(std::vector<Texto*> op, int x, int y, int vm, int vfx) {
    options = op;
    currentOpt = 0;
    posX = x;
    posY = y;
    musicVol = vm;
    fxVol = vfx;
    fondo = new Fondo("./resources/fondos/fondomenu.png", false);

    tmVol = new Texto(musicVol * 10, 18, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    tfxVol = new Texto(fxVol * 10, 18, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    puntero = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/puntero.png", true);
    puntero1 = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/puntero.png", true);
    puntero2 = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/puntero.png", true);


    int inc;
    for (int i = 0; i < options.size(); i++) {
        inc = i * 20;
        options[i]->setPos(posX, posY + inc);
    }
}

void Menu::update() {
    int inc;
    int w = Motorgrafico::getInstance()->getWindowWidth();
    int h = Motorgrafico::getInstance()->getWindowHeight();


    fondo->setPosition(w / 2, h / 2);
    for (int i = 0; i < options.size(); i++) {
        inc = i * 20;
        if (i == currentOpt) {
            options[i]->setPos(posX + 5, posY + inc);
            options[i]->setColor(0, 255, 0);
            puntero->setPos(posX - 20, posY + 16 + inc);
            puntero->setAngle(90);


        } else {
            options[i]->setPos(posX, posY + inc);
            options[i]->setColor(255, 0, 0);
        }
    }

}

void Menu::gameUpdate() {
    int inc;
    int incX;

    fondo->Update();
    for (int i = 0; i < options.size(); i++) {
        inc = i * 20;

        if (i == currentOpt) {
            options[i]->setPos(posX + 5, posY + inc);
            options[i]->setColor(0, 255, 0);
            puntero->setPos(posX - 20, posY + 16 + inc);
            puntero->setAngle(90);

            if (i != 3) {
                puntero1->setPos(posX + 85, posY + 16 + inc);
                puntero1->setAngle(270);


                if (i == 0) {
                    trounds->setPos(posX + 100, posY + inc);
                    trounds->setColor(0, 255, 0);
                    incX = 100 + 15 * trounds->getStringLength();
                    puntero2->setPos(posX + 130, posY + 16 + inc);
                    puntero2->setAngle(90);
                }

                if (i == 1) {
                    ttime->setPos(posX + 100, posY + inc);
                    ttime->setColor(0, 255, 0);
                    incX = 100 + 15 * ttime->getStringLength();
                    puntero2->setPos(posX + 130, posY + 16 + inc);
                    puntero2->setAngle(90);
                }

                if (i == 2) {
                    tmode->setPos(posX + 100, posY + inc);
                    tmode->setColor(0, 255, 0);
                    if (mode == 1) incX = 170;
                    if (mode == 2) incX = 270;
                    if (mode == 3) incX = 240;

                    puntero2->setPos(posX + incX, posY + 16 + inc);
                    puntero2->setAngle(90);
                }
            }

        } else {
            options[i]->setPos(posX, posY + inc);
            options[i]->setColor(255, 0, 0);

            if (i == 0) {
                trounds->setPos(posX + 100, posY + inc);
                trounds->setColor(255, 0, 0);
            }

            if (i == 1) {
                ttime->setPos(posX + 100, posY + inc);
                ttime->setColor(255, 0, 0);
            }

            if (i == 2) {
                tmode->setPos(posX + 100, posY + inc);
                tmode->setColor(255, 0, 0);
            }

        }
    }
}

void Menu::optionsUpdate() {
    int inc;
    int incX;

    fondo->Update();
    for (int i = 0; i < options.size(); i++) {
        inc = i * 20;

        if (i == currentOpt) {
            options[i]->setPos(posX + 5, posY + inc);
            options[i]->setColor(0, 255, 0);
            puntero->setPos(posX - 20, posY + 16 + inc);
            puntero->setAngle(90);

            if (i != 2) {
                puntero1->setPos(posX + 285, posY + 16 + inc);
                puntero1->setAngle(270);

                if (i == 0) {
                    tmVol->setPos(posX + 300, posY + inc);
                    tmVol->setColor(0, 255, 0);

                    puntero2->setPos(posX + 340, posY + 16 + inc);
                    puntero2->setAngle(90);
                }

                if (i == 1) {
                    tfxVol->setPos(posX + 300, posY + inc);
                    tfxVol->setColor(0, 255, 0);

                    puntero2->setPos(posX + 340, posY + 16 + inc);
                    puntero2->setAngle(90);
                }
            }

        } else {
            options[i]->setPos(posX, posY + inc);
            options[i]->setColor(255, 0, 0);

            if (i == 0) {
                tmVol->setPos(posX + 300, posY + inc);
                tmVol->setColor(255, 0, 0);
            }

            if (i == 1) {
                tfxVol->setPos(posX + 300, posY + inc);
                tfxVol->setColor(255, 0, 0);
            }
        }
    }
}

void Menu::goDown() {

    if (currentOpt == options.size() - 1) {
        currentOpt = 0;
    } else {

        currentOpt++;
    }
}

void Menu::goUp() {

    if (currentOpt == 0) {
        currentOpt = options.size() - 1;
    } else {
        currentOpt--;
    }
}

void Menu::render() {

    Motorgrafico::getInstance()->clearWindow();
    Motorgrafico::getInstance()->setHudCameraView();
    
    int i = 0;

    puntero->updateBody();
    fondo->Render();
    Motorgrafico::getInstance()->draw(puntero->getShape());
    while (i < options.size()) {
        Motorgrafico::getInstance()->draw(options[i]->getDrawable());
        i++;
    }
    Motorgrafico::getInstance()->displayWindow();
}

void Menu::renderGameMenu() {

    Motorgrafico::getInstance()->clearWindow();
    Motorgrafico::getInstance()->setHudCameraView();


    int i = 0;
    fondo->Render();
    puntero->updateBody();
    puntero1->updateBody();
    puntero2->updateBody();

    Motorgrafico::getInstance()->draw(puntero->getShape());
    if (currentOpt != 3) {
        Motorgrafico::getInstance()->draw(puntero1->getShape());
        Motorgrafico::getInstance()->draw(puntero2->getShape());
    }

    while (i < options.size()) {
        Motorgrafico::getInstance()->draw(options[i]->getDrawable());
        i++;
    }
    Motorgrafico::getInstance()->draw(trounds->getDrawable());
    Motorgrafico::getInstance()->draw(ttime->getDrawable());
    Motorgrafico::getInstance()->draw(tmode->getDrawable());

    Motorgrafico::getInstance()->displayWindow();
}

void Menu::renderOptionsMenu() {

    Motorgrafico::getInstance()->clearWindow();
    Motorgrafico::getInstance()->setHudCameraView();


    int i = 0;
    fondo->Render();
    puntero->updateBody();
    puntero1->updateBody();
    puntero2->updateBody();

    Motorgrafico::getInstance()->draw(puntero->getShape());
    if (currentOpt != 2) {
        Motorgrafico::getInstance()->draw(puntero1->getShape());
        Motorgrafico::getInstance()->draw(puntero2->getShape());
    }

    while (i < options.size()) {
        Motorgrafico::getInstance()->draw(options[i]->getDrawable());
        i++;
    }

    Motorgrafico::getInstance()->draw(tmVol->getDrawable());
    Motorgrafico::getInstance()->draw(tfxVol->getDrawable());

    Motorgrafico::getInstance()->displayWindow();
}

void Menu::input(int &state, Menu* menu) {
    Motorgrafico::getInstance()->eventListener(state, menu);
}

int Menu::getCurrentOption() {
    return currentOpt;
}

void Menu::increaseRounds() {

    if (rounds < 10) {
        rounds++;
        trounds->setTexto(rounds);
    }

}

void Menu::increaseTime() {

    if (time < 100) {
        time += 10;
        ttime->setTexto(time);
    }
}

void Menu::increaseMode() {

    if (mode < 3) {
        mode++;
        tmode->setTexto(modes[mode - 1]);
    }

}

void Menu::decreaseRounds() {

    if (rounds > 1) {
        rounds--;
        trounds->setTexto(rounds);
    }

}

void Menu::decreaseTime() {

    if (time > 10) {
        time -= 10;
        ttime->setTexto(time);
    }

}

void Menu::decreaseMode() {
    if (mode > 1) {
        mode--;

        tmode->setTexto(modes[mode - 1]);
    }
}

void Menu::increaseMusicVol() {
    if (musicVol < 10) {
        musicVol++;
        tmVol->setTexto(musicVol * 10);
    }
}

void Menu::increaseFXVol() {
    if (fxVol < 10) {
        fxVol++;
        tfxVol->setTexto(fxVol * 10);
    }
}

void Menu::decreaseMusicVol() {
    if (musicVol > 0) {
        musicVol--;
        tmVol->setTexto(musicVol * 10);
    }
}

void Menu::decreaseFXVol() {
    if (fxVol > 0) {
        fxVol--;
        tfxVol->setTexto(fxVol * 10);
    }
}

Menu::~Menu() {
}