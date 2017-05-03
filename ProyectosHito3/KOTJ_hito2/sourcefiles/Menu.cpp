
/* 
 * File:   Menu.cpp
 * Author: pedro
 * 
 * Created on 25 de abril de 2017, 14:27
 */

#include "../headerfiles/Menu.h"
#include "../motorgrafico/headerfiles/Motorgrafico.h"

Menu::Menu(std::vector<Texto*> op, float x, float y) {
    options = op;
    currentOpt = 0;
    posX = x;
    posY = y;

    triangle = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/triangle.png", true);

    int inc;
    for (int i = 0; i < options.size(); i++) {
        inc = i * 20;
        options[i]->setPos(posX, posY + inc);
    }
}

Menu::Menu(std::vector<Texto*> op, float x, float y, int r, float t, int m) {

    options = op;
    currentOpt = 0;
    posX = x;
    posY = y;

    rounds = r;
    time = t;
    mode = m;
    modes = std::vector<string>(4);
    modes[0] = "Normal";
    modes[1] = "Recolectar monedas";
    modes[2] = "Patata caliente";
    modes[3] = "Clavar la bandera";

    trounds = new Texto(rounds, 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    ttime = new Texto(time, 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    tmode = new Texto(modes[mode - 1], 18, "./resources/fonts/bits.ttf", 255, 0, 0);
    triangle = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/triangle.png", true);
    triangle1 = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/triangle.png", true);
    triangle2 = new VisibleBody(posX, posY, 16, 16, "./resources/sprites/triangle.png", true);

    int inc;
    for (int i = 0; i < options.size(); i++) {
        inc = i * 20;
        options[i]->setPos(posX, posY + inc);
    }
}

void Menu::update() {
    int inc;

    for (int i = 0; i < options.size(); i++) {
        inc = i * 20;
        if (i == currentOpt) {
            options[i]->setPos(posX + 5, posY + inc);
            options[i]->setColor(0, 255, 0);
            triangle->setPos(posX - 20, posY + 16 + inc);
            triangle->setAngle(90);


        } else {
            options[i]->setPos(posX, posY + inc);
            options[i]->setColor(255, 0, 0);
        }
    }
}

void Menu::gameUpdate() {
    int inc;
    int incX;

    for (int i = 0; i < options.size(); i++) {
        inc = i * 20;

        if (i == currentOpt) {
            options[i]->setPos(posX + 5, posY + inc);
            options[i]->setColor(0, 255, 0);
            triangle->setPos(posX - 20, posY + 16 + inc);
            triangle->setAngle(90);

            if (i != 3) {
                triangle1->setPos(posX + 85, posY + 16 + inc);
                triangle1->setAngle(270);


                if (i == 0) {
                    trounds->setPos(posX + 100, posY + inc);
                    trounds->setColor(0, 255, 0);
                    incX = 100 + 15 * trounds->getStringLength();
                    triangle2->setPos(posX + 130, posY + 16 + inc);
                    triangle2->setAngle(90);
                }

                if (i == 1) {
                    ttime->setPos(posX + 100, posY + inc);
                    ttime->setColor(0, 255, 0);
                    incX = 100 + 15 * ttime->getStringLength();
                    triangle2->setPos(posX + 130, posY + 16 + inc);
                    triangle2->setAngle(90);
                }

                if (i == 2) {
                    tmode->setPos(posX + 100, posY + inc);
                    tmode->setColor(0, 255, 0);
                    if (mode == 1) incX = 170;
                    if (mode == 2) incX = 270;
                    if (mode == 3) incX = 240;

                    triangle2->setPos(posX + incX, posY + 16 + inc);
                    triangle2->setAngle(90);
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

void Menu::goDown() {

    if (currentOpt == options.size() - 1) currentOpt = 0;
    else currentOpt++;
}

void Menu::goUp() {

    if (currentOpt == 0) currentOpt = options.size() - 1;
    else currentOpt--;
}

void Menu::render() {

    Motorgrafico::getInstance()->clearWindow();
    Motorgrafico::getInstance()->setHudCameraView();

    int i = 0;

    triangle->updateBody();
    Motorgrafico::getInstance()->draw(triangle->getShape());
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

    triangle->updateBody();
    triangle1->updateBody();
    triangle2->updateBody();

    Motorgrafico::getInstance()->draw(triangle->getShape());
    if (currentOpt != 3) {
        Motorgrafico::getInstance()->draw(triangle1->getShape());
        Motorgrafico::getInstance()->draw(triangle2->getShape());
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
    if (time < 90) {
        time += 10;
        ttime->setTexto(time);
    }
}

void Menu::increaseMode() {
    if (mode < 4) {
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

Menu::~Menu() {
}

