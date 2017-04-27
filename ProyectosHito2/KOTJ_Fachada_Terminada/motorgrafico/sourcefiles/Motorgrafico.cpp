/* 
 * File:   Motorgrafico.cpp
 * Author: amygwyllion
 * 
 * Created on 11 de abril de 2017, 20:17
 */

#include "../headerfiles/Motorgrafico.h"

static Motorgrafico* instance;

Motorgrafico* Motorgrafico::getInstance() {
    if (instance == NULL) instance = new Motorgrafico();
    return (instance);
}

Motorgrafico::Motorgrafico(){
    temporizador = new Temporizador(20, screenWidth / 2, 0, 40);
    partida = Partida::getInstance();
    window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "KingOfTheJungle 2k17 Turbo Power Edition", sf::Style::Titlebar | sf::Style::Close);
    setFramerateLimitOn(60);
    mainCamera = new sf::View(sf::FloatRect(0, 0, screenWidth, screenHeight));
    hudCamera = new sf::View(sf::FloatRect(0, 0, screenWidth, screenHeight));
    setMainCameraView();
    setHudCameraView();
}

Motorgrafico::Motorgrafico(const Motorgrafico& orig) {
}

void Motorgrafico::setFramerateLimitOn(int framerate){
    window->setFramerateLimit(60);
}

void Motorgrafico::setMainCameraView(){
    window->setView(*mainCamera);
}

void Motorgrafico::setHudCameraView(){
    window ->setView(*hudCamera);
}

void Motorgrafico::cameraSetTransform(){
    int total = 0;
    float posX = 0;
    float posY = 0;

    float newSize = screenWidth;
    float minSize = screenWidth;

    float ratio = screenWidth / (float) screenHeight;
    float maxDifferenceX = 0;
    float maxDifferenceY = 0;

    //Posición
    for (int i = 0; i < partida->worldPlayer.size(); i++) {
        if (!partida->worldPlayer.at(i)->isPlayerDead()) {
            posX += partida->worldPlayer.at(i)->getPositionX();
            posY += partida->worldPlayer.at(i)->getPositionY();
            total++;
        }
    }

    //Tenemos en cuenta las esquinas del nivel
    posX += screenWidth*MPP;
    posY += screenHeight*MPP;
    total++;

    posX += 0;
    posY += 0;
    total++;

    posX += screenWidth*MPP;
    posY += 0;
    total++;

    posX += 0;
    posY += screenHeight*MPP;
    total++;

    posX = posX / total;
    posY = posY / total;
    mainCamera->setCenter(posX * PPM, posY * PPM);


    //Zoom
    for (int i = 0; i < partida->worldPlayer.size(); i++) {
        if (!partida->worldPlayer.at(i)->isPlayerDead()) {
            float currentPosX = partida->worldPlayer.at(i)->getPositionX();
            if (abs(currentPosX - posX) > maxDifferenceX) maxDifferenceX = abs(currentPosX - posX);

            float currentPosY = partida->worldPlayer.at(i)->getPositionY();
            if (abs(currentPosY - posY) > maxDifferenceY) maxDifferenceY = abs(currentPosY - posY);
        }
    }

    if (maxDifferenceX > maxDifferenceY * ratio) {
        maxDifferenceX += 2;
        newSize = abs(maxDifferenceX * 2 * PPM);
        if (newSize < minSize) newSize = minSize;
        mainCamera->setSize(sf::Vector2f(newSize, newSize / ratio));
    } else {
        maxDifferenceY += (2 / ratio);
        newSize = abs(maxDifferenceY * 2 * PPM);
        if (newSize < minSize / ratio) newSize = minSize / ratio;
        mainCamera->setSize(sf::Vector2f(newSize * ratio, newSize));
    }

    //Ponerlo todo
    setMainCameraView();

}

void Motorgrafico::eventListener(){
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::JoystickConnected:
                partida->addPlayerJoystick(event.joystickConnect.joystickId);
                break;

            case sf::Event::JoystickMoved:
                if (event.joystickMove.axis == Joystick::X) {
                    partida->worldControlador.at(partida->findControladorWithId(event.joystickMove.joystickId))->checkAxisX(event.joystickMove.position);
                }
                if (event.joystickMove.axis == Joystick::Y) {
                    partida->worldControlador.at(partida->findControladorWithId(event.joystickMove.joystickId))->checkAxisY(event.joystickMove.position);
                }
                break;

            case sf::Event::JoystickButtonPressed:
                partida->worldControlador.at(partida->findControladorWithId(event.joystickButton.joystickId))->pressUpdateState(event.joystickButton.button);
                break;

            case sf::Event::JoystickButtonReleased:
                partida->worldControlador.at(partida->findControladorWithId(event.joystickButton.joystickId))->releaseUpdateState(event.joystickButton.button);
                break;

            case sf::Event::KeyPressed:
                if (partida->getUsingKeyboard() == true)
                    partida->worldControlador.at(partida->findKeyboardControlador())->pressUpdateState(event.key.code);
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window->close();
                        break;
                    case sf::Keyboard::F2:
                        if (partida->getUsingKeyboard() == false) {
                            partida->addPlayerKeyboard();
                            partida->setUsingKeyboard(true);
                        }
                        break;
                }
                break;

            case sf::Event::KeyReleased:
                if (partida->getUsingKeyboard() == true) partida->worldControlador.at(partida->findKeyboardControlador())->releaseUpdateState(event.key.code);
                break;
        }
    }
}

void Motorgrafico::clearWindow(){
    window->clear(sf::Color::Black);
}

void Motorgrafico::updateWindow(){
    resetFrameTime();
    setHudCameraView();
    updateTemporizador();
    setMainCameraView();
}

void Motorgrafico::displayWindow(){
    window->display();
}

template <class T1> void Motorgrafico::draw(T1& object){
    window->draw(object);  
}
void Motorgrafico::draw(SpriteAnimated &object){
    window->draw(object);
}
void Motorgrafico::draw(sf::RectangleShape object){
    window->draw(object);
}
void Motorgrafico::draw(sf::CircleShape object){
    window->draw(object);
}

sf::RenderWindow *Motorgrafico::getRenderWindow(){
    return window;
}

void Motorgrafico::updateTemporizador(){
    temporizador->Update();
}

void Motorgrafico::drawTemporizador(){
    temporizador->Draw(window);
}

void Motorgrafico::resetFrameTime(){
    frameTime = frameClock.restart();
}

sf::Time Motorgrafico::getFrameTime(){
    return frameTime;
}

Motorgrafico::~Motorgrafico(){
}