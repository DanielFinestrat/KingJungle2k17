
/* 
 * File:   Menu.cpp
 * Author: pedro
 * 
 * Created on 25 de abril de 2017, 14:27
 */

#include "headerfiles/Menu.h"
#include "motorgrafico/headerfiles/Motorgrafico.h"
#include <iostream>
#include <sstream>

Menu::Menu(std::vector<Texto*> op, int x, int y) {
    options = op;
    currentOpt = 0;
    posX = x;
    posY = y;

    fondo = new Fondo("./resources/fondos/fondomenu.png", false);

    puntero = new VisibleBody(posX, posY, 387 / 3, 200 / 3, "./resources/sprites/puntero.png", true);

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
    modes[0] = "Random";
    modes[1] = "Todos contra Todos";
    modes[2] = "Recolectar monedas";
    fondo = new Fondo("./resources/fondos/fondomenu.png", false);

    trounds = new Texto(rounds, 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    ttime = new Texto(time, 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    tmode = new Texto(modes[mode - 1], 25, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    puntero = new VisibleBody(posX, posY, 387 / 3, 200 / 3, "./resources/sprites/puntero.png", true);

    int inc;
    for (int i = 0; i < options.size(); i++) {
        inc = i * 55;
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

    tmVol = new Texto(musicVol * 10, 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    tfxVol = new Texto(fxVol * 10, 40, "./resources/fonts/newrotic.ttf", 255, 0, 0);
    puntero = new VisibleBody(posX, posY, 387 / 3, 200 / 3, "./resources/sprites/puntero.png", true);

    int inc;
    for (int i = 0; i < options.size(); i++) {
        inc = i * 55;
        options[i]->setPos(posX, posY + inc);
    }
}

void Menu::update() {
    int inc;
    int w = Motorgrafico::getInstance()->getWindowWidth();
    int h = Motorgrafico::getInstance()->getWindowHeight();
    fondo->setPosition(w / 2, h / 2);

    for (int i = 0; i < options.size(); i++) {
        inc = i * 55;
        if (i == currentOpt) {
            options[i]->setPos(posX + 5, posY + inc);
            options[i]->setColor(100, 0, 0);
            puntero->setPos(posX - 60, posY + 16 + inc);

        } else {
            options[i]->setPos(posX, posY + inc);
            options[i]->setColor(0, 0, 0);
        }
    }

}

void Menu::gameUpdate() {
    int inc;
    int incX;
    int w = Motorgrafico::getInstance()->getWindowWidth();
    int h = Motorgrafico::getInstance()->getWindowHeight();
    fondo->setPosition(w / 2, h / 2);

    for (int i = 0; i < options.size(); i++) {
        inc = i * 55;

        if (i == currentOpt) {
            options[i]->setPos(posX + 5, posY + inc);
            options[i]->setColor(100, 0, 0);
            puntero->setPos(posX - 60, posY + 16 + inc);


            if (i != 3) {

                if (i == 0) {
                    stringstream ss;
                    ss << "<" << rounds << ">";
                    trounds->setTexto(ss.str());
                    trounds->setPos(posX + 300, posY + inc);
                    trounds->setColor(100, 0, 0);
                    incX = 100 + 15 * trounds->getStringLength();
                }

                if (i == 1) {
                    stringstream ss;
                    ss << "<" << time << ">";
                    ttime->setTexto(ss.str());
                    ttime->setPos(posX + 300, posY + inc);
                    ttime->setColor(100, 0, 0);
                    incX = 100 + 15 * ttime->getStringLength();
                }

                if (i == 2) {
                    stringstream ss;
                    ss << "<" << modes[mode - 1] << ">";
                    tmode->setTexto(ss.str());
                    tmode->setPos(posX + 300, posY + inc);
                    tmode->setColor(100, 0, 0);
                    if (mode == 1) incX = 170;
                    if (mode == 2) incX = 270;
                    //if (mode == 3) incX = 240;
                }
            }

        } else {
            options[i]->setPos(posX, posY + inc);
            options[i]->setColor(0, 0, 0);

            if (i == 0) {
                trounds->setTexto(rounds);
                trounds->setPos(posX + 300, posY + inc);
                trounds->setColor(0, 0, 0);
            }

            if (i == 1) {
                ttime->setTexto(time);
                ttime->setPos(posX + 300, posY + inc);
                ttime->setColor(0, 0, 0);
            }

            if (i == 2) {
                tmode->setTexto(modes[mode - 1]);
                tmode->setPos(posX + 300, posY + inc);
                tmode->setColor(0, 0, 0);
            }

        }
    }
}

void Menu::optionsUpdate() {
    int inc;
    int incX;

    int w = Motorgrafico::getInstance()->getWindowWidth();
    int h = Motorgrafico::getInstance()->getWindowHeight();
    fondo->setPosition(w / 2, h / 2);
    for (int i = 0; i < options.size(); i++) {
        inc = i * 55;

        if (i == currentOpt) {
            options[i]->setPos(posX + 5, posY + inc);
            options[i]->setColor(100, 0, 0);
            puntero->setPos(posX - 60, posY + 16 + inc);

            if (i != 2) {

                if (i == 0) {
                    stringstream ss;
                    ss << "<" << musicVol * 10 << ">";
                    tmVol->setTexto(ss.str());
                    tmVol->setPos(posX + 500, posY + inc);
                    tmVol->setColor(100, 0, 0);
                }

                if (i == 1) {
                    stringstream ss;
                    ss << "<" << fxVol * 10 << ">";
                    tfxVol->setTexto(ss.str());
                    tfxVol->setPos(posX + 500, posY + inc);
                    tfxVol->setColor(100, 0, 0);
                }
            }

        } else {
            options[i]->setPos(posX, posY + inc);
            options[i]->setColor(0, 0, 0);

            if (i == 0) {
                tmVol->setTexto(musicVol * 10);
                tmVol->setPos(posX + 500, posY + inc);
                tmVol->setColor(0, 0, 0);
            }

            if (i == 1) {
                tfxVol->setTexto(fxVol * 10);
                tfxVol->setPos(posX + 500, posY + inc);
                tfxVol->setColor(0, 0, 0);
            }
        }
    }
}

void Menu::goDown() {
    relojVertical.restartClock();
    difTimeVertical += relojVertical.getDeltaTimeAsSeconds();
    if (difTimeVertical >= 0.25) {
        difTimeVertical = 0.0f;
        if (currentOpt == options.size() - 1) {
            currentOpt = 0;
        } else {
            currentOpt++;
        }
    }
}

void Menu::goUp() {
    relojVertical.restartClock();
    difTimeVertical += relojVertical.getDeltaTimeAsSeconds();
    if (difTimeVertical >= 0.25) {
        difTimeVertical = 0.0f;
        if (currentOpt == 0) {
            currentOpt = options.size() - 1;
        } else {
            currentOpt--;
        }
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
    Motorgrafico::getInstance()->draw(puntero->getShape());

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
    Motorgrafico::getInstance()->draw(puntero->getShape());

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
    relojHorizontal.restartClock();
    difTimeHorizontal += relojHorizontal.getDeltaTimeAsSeconds();
    if (difTimeHorizontal >= 0.25) {
        difTimeHorizontal = 0.0f;
        if (rounds < 10) {
            rounds++;
            stringstream ss;
            ss << "<" << rounds << ">";
            trounds->setTexto(ss.str());

        }
    }
}

void Menu::increaseTime() {
    relojHorizontal.restartClock();
    difTimeHorizontal += relojHorizontal.getDeltaTimeAsSeconds();
    if (difTimeHorizontal >= 0.25) {
        difTimeHorizontal = 0.0f;
        if (time < 100) {
            time += 10;
            stringstream ss;
            ss << "<" << time << ">";
            ttime->setTexto(ss.str());
        }
    }
}

void Menu::increaseMode() {
    relojHorizontal.restartClock();
    difTimeHorizontal += relojHorizontal.getDeltaTimeAsSeconds();
    if (difTimeHorizontal >= 0.25) {
        difTimeHorizontal = 0.0f;
        if (mode < 3) {
            mode++;
            stringstream ss;
            ss << "<" << modes[mode - 1] << ">";
            tmode->setTexto(ss.str());
        }
    }
}

void Menu::decreaseRounds() {
    relojHorizontal.restartClock();
    difTimeHorizontal += relojHorizontal.getDeltaTimeAsSeconds();
    if (difTimeHorizontal >= 0.25) {
        difTimeHorizontal = 0.0f;
        if (rounds > 1) {
            rounds--;
            stringstream ss;
            ss << "<" << rounds << ">";
            trounds->setTexto(ss.str());
        }
    }
}

void Menu::decreaseTime() {
    relojHorizontal.restartClock();
    difTimeHorizontal += relojHorizontal.getDeltaTimeAsSeconds();
    if (difTimeHorizontal >= 0.25) {
        difTimeHorizontal = 0.0f;
        if (time > 10) {
            time -= 10;
            stringstream ss;
            ss << "<" << time << ">";
            ttime->setTexto(ss.str());
        }
    }
}

void Menu::decreaseMode() {
    relojHorizontal.restartClock();
    difTimeHorizontal += relojHorizontal.getDeltaTimeAsSeconds();
    if (difTimeHorizontal >= 0.25) {
        difTimeHorizontal = 0.0f;
        if (mode > 1) {
            mode--;
            stringstream ss;
            ss << "<" << modes[mode - 1] << ">";
            tmode->setTexto(ss.str());
        }
    }
}

void Menu::increaseMusicVol() {
    relojHorizontal.restartClock();
    difTimeHorizontal += relojHorizontal.getDeltaTimeAsSeconds();
    if (difTimeHorizontal >= 0.25) {
        difTimeHorizontal = 0.0f;
        if (musicVol < 10) {
            musicVol++;
            stringstream ss;
            ss << "<" << musicVol * 10 << ">";
            tmVol->setTexto(ss.str());
        }
    }
}

void Menu::increaseFXVol() {
    relojHorizontal.restartClock();
    difTimeHorizontal += relojHorizontal.getDeltaTimeAsSeconds();
    if (difTimeHorizontal >= 0.25) {
        difTimeHorizontal = 0.0f;
        if (fxVol < 10) {
            fxVol++;
            stringstream ss;
            ss << "<" << fxVol * 10 << ">";
            tfxVol->setTexto(ss.str());
        }
    }
}

void Menu::decreaseMusicVol() {
    relojHorizontal.restartClock();
    difTimeHorizontal += relojHorizontal.getDeltaTimeAsSeconds();
    if (difTimeHorizontal >= 0.25) {
        difTimeHorizontal = 0.0f;
        if (musicVol > 0) {
            musicVol--;
            stringstream ss;
            ss << "<" << musicVol * 10 << ">";
            tmVol->setTexto(ss.str());
        }
    }
}

void Menu::decreaseFXVol() {
    relojHorizontal.restartClock();
    difTimeHorizontal += relojHorizontal.getDeltaTimeAsSeconds();
    if (difTimeHorizontal >= 0.25) {
        difTimeHorizontal = 0.0f;
        if (fxVol > 0) {
            fxVol--;
            stringstream ss;
            ss << "<" << fxVol * 10 << ">";
            tfxVol->setTexto(ss.str());
        }
    }
}

void Menu::goUpKeyboard() {
    if (currentOpt == 0) {
        currentOpt = options.size() - 1;
    } else {
        currentOpt--;
    }
}

void Menu::goDownKeyboard() {
    if (currentOpt == options.size() - 1) {
        currentOpt = 0;
    } else {
        currentOpt++;
    }
}

int Menu::getTiempo() {
    return time;
}

int Menu::getPuntos() {
    return rounds;
}

int Menu::getMode() {
    return mode;
}

Menu::~Menu() {
}