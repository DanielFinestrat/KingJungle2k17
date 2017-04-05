/* 
 * File:   Partida.cpp
 * Author: daniel
 * 
 * Created on 26 de marzo de 2017, 13:13
 */

#include "../headerfiles/Partida.h"
using namespace sf;

static Partida* instance;

Partida::Partida() {
    window = new RenderWindow(VideoMode(screenWidth, screenHeight), "KingOfTheJungle 2k17 Turbo Power Edition", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);
    world = new b2World(b2Vec2(0.0f, 9.8f));
    world->SetContactListener(&myContactListener);
    temporizador = new Temporizador(20, b2Vec2(screenWidth / 2, 0), 40);
    usingKeyboard = false;

    mainCamera = new sf::View(sf::FloatRect(0, 0, screenWidth, screenHeight));
    hudCamera = new sf::View(sf::FloatRect(0, 0, screenWidth, screenHeight));
    window->setView(*mainCamera);
    window ->setView(*hudCamera);
}

Partida::Partida(const Partida& orig) {
}

Partida* Partida::getInstance() {
    if (instance == NULL) instance = new Partida();
    return (instance);
}

void Partida::Input() {

    Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                window->close();
                break;

            case Event::JoystickConnected:
                addPlayerJoystick(event.joystickConnect.joystickId);
                break;

            case Event::JoystickMoved:
                if (event.joystickMove.axis == Joystick::X) {
                    worldControlador.at(findControladorWithId(event.joystickMove.joystickId))->checkAxisX(event.joystickMove.position);
                }
                if (event.joystickMove.axis == Joystick::Y) {
                    worldControlador.at(findControladorWithId(event.joystickMove.joystickId))->checkAxisY(event.joystickMove.position);
                }
                break;

            case Event::JoystickButtonPressed:
                worldControlador.at(findControladorWithId(event.joystickButton.joystickId))->pressUpdateState(event.joystickButton.button);
                break;

            case Event::JoystickButtonReleased:
                worldControlador.at(findControladorWithId(event.joystickButton.joystickId))->releaseUpdateState(event.joystickButton.button);
                break;

            case Event::KeyPressed:
                if (usingKeyboard)
                    worldControlador.at(findKeyboardControlador())->pressUpdateState(event.key.code);
                switch (event.key.code) {
                    case Keyboard::Escape:
                        window->close();
                        break;
                    case Keyboard::F2:
                        if (!usingKeyboard) {
                            addPlayerKeyboard();
                            usingKeyboard = true;
                        }
                        break;
                }
                break;

            case Event::KeyReleased:
                if (usingKeyboard) worldControlador.at(findKeyboardControlador())->releaseUpdateState(event.key.code);
                break;
        }
    }

}

void Partida::erasePlayers() {
    for (int i = 0; i < players2Delete.size(); i++) {

        players2Delete.at(i)->die(players2Delete.at(i)->getDirMoving());
    }
    players2Delete.clear();
}

void Partida::eraseBullets() {
    set<Bala*>::iterator itBala = bullets2Delete.begin();

    for (; itBala != bullets2Delete.end(); itBala++) {
        Bala* dyingBala = *itBala;
        if (dyingBala->explosion == true) {
            b2Vec2 position = dyingBala->m_pBody->GetPosition();

            Explosion *nueva;
            nueva = new Explosion(dyingBala->m_pBody->GetWorld(), sf::Vector2f(position.x * PPM, position.y * PPM), 1.0f, 0.05f, 0.5f);
            worldExplo.insert(nueva);
        }
        worldBullets.erase(dyingBala);
        delete dyingBala;
        dyingBala = NULL;
    }
    bullets2Delete.clear();
}

void Partida::eraseExplo() {
    set<Explosion*>::iterator itExplo = explo2Delete.begin();
    set<Explosion*>::iterator itEnd = explo2Delete.end();

    for (; itExplo != itEnd; itExplo++) {
        Explosion* dyingExplo = *itExplo;
        worldExplo.erase(dyingExplo);
        delete dyingExplo;
        dyingExplo = NULL;
    }
    explo2Delete.clear();
}

void Partida::Erase() {
    eraseBullets();
    erasePlayers();
    eraseExplo();
}

void Partida::Update() {
    world->Step(TIMESTEP, VELITER, POSITER);
    Time frameTime = frameClock.restart();
    window->setView(*hudCamera);
    temporizador->Update();
    window->setView(*mainCamera);
    updateWeapons();
    updatePlayers(frameTime);
    updateBullets();
    updateExplo();

    cameraSetTransform();
}

void Partida::Render() {
    window->clear(sf::Color::Black);
    window->setView(*mainCamera);
    drawPlatforms();
    drawPlayers();
    drawWeapons();
    drawBullets();
    drawExplo();
    window->setView(*hudCamera);
    temporizador->Draw(window);
    window->display();
}

void Partida::drawPlatforms() {
    for (int i = 0; i < worldPlatforms.size(); i++) {
        worldPlatforms.at(i)->Render(window);
    }
}

void Partida::drawPlayers() {
    for (int i = 0; i < worldPlayer.size(); i++) {
        window->draw(worldPlayer.at(i)->getPlayerSprite());
    }
    // if (usingKeyboard) window->draw(playerKeyboard->player->getPlayerSprite());
}

void Partida::drawWeapons() {
    for (int i = 0; i < worldWeapons.size(); i++) {
        window->draw(*(worldWeapons.at(i)->m_Shape));
    }
}

void Partida::drawBullets() {
    set<Bala*>::iterator itBala = worldBullets.begin();
    set<Bala*>::iterator endBala = worldBullets.end();
    for (; itBala != endBala; ++itBala) {
        Bala* renderBala = *itBala;
        window->draw(*(renderBala->m_Shape));
    }
}

void Partida::drawExplo() {
    set<Explosion*>::iterator itExplo = worldExplo.begin();
    set<Explosion*>::iterator endExplo = worldExplo.end();
    for (; itExplo != endExplo; ++itExplo) {
        Explosion* renderExplo = *itExplo;
        window->draw(*(renderExplo->m_Shape));
    }
}

int Partida::findKeyboardControlador() {
    int index = -1;

    for (int i = 0; i < worldControlador.size(); i++) {
        if (worldControlador.at(i)->tipo.compare("Keyboard") == 0) {
            index = i;
            break;
        }
    }

    return index;
}

int Partida::findControladorWithId(int id) {
    int index = -1;

    for (int i = 0; i < worldControlador.size(); i++) {
        if (worldControlador.at(i)->tipo.compare("Joystick") == 0 && worldControlador.at(i)->id == id) {
            index = i;
            break;
        }
    }

    return index;
}

void Partida::checkJoysticksConnected() {

    /*addPlayerJoystick(&playerJoysticks, 0);
    addPlayerJoystick(&playerJoysticks, 1);
    addPlayerJoystick(&playerJoysticks, 2);
    addPlayerJoystick(&playerJoysticks, 3);*/

    Joystick joystickManager;
    for (int i = 0; i < 4; i++) {
        if (joystickManager.isConnected(i)) {
            addPlayerJoystick(i);
        }
    }
}

void Partida::addPlayerJoystick(int id) {
    //Para saber si la tenemos que añador
    bool add = true;

    //Comprobamos si existe el mando y actualizamos la condición
    for (int i = 0; i < worldControlador.size() && add; i++) {
        if (worldControlador.at(i)->tipo.compare("Joystick") == 0 && worldControlador.at(i)->id == id) add = false;
    }

    //Añadimos en funcion de la condición
    if (add) {
        PlayerJoystick* p = new PlayerJoystick(id, world);
        worldControlador.push_back(p);
    }
}

void Partida::addPlayerKeyboard() {
    worldControlador.push_back(new PlayerKeyboard(world));
}

void Partida::respawn() {
    for (int i = 0; i < worldPlayer.size(); i++) {
        Player* player = worldPlayer.at(i);
        player->setPosition((i + 1) * screenWidth / 5, screenHeight - 100);
        player->respawn();
    }
    /* if (usingKeyboard) {
         playerKeyboard->player->setPosition((4) * screenWidth / 5, screenHeight - 100);
         playerKeyboard->player->respawn();
     }*/
}

void Partida::updatePlayers(Time frameTime) {
    for (int i = 0; i < worldPlayer.size(); i++) {
        worldPlayer.at(i)->update(frameTime);
    }
}

void Partida::updateWeapons() {
    for (int i = 0; i < worldWeapons.size(); i++) {
        worldWeapons.at(i)->update();
    }
}

void Partida::updateBullets() {
    set<Bala*>::iterator itBala = worldBullets.begin();
    set<Bala*>::iterator endBala = worldBullets.end();
    for (; itBala != endBala; ++itBala) {
        Bala* updateBala = *itBala;
        updateBala->Update_Shape();
    }

}

void Partida::updateExplo() {
    set<Explosion*>::iterator itExplo = worldExplo.begin();
    set<Explosion*>::iterator endExplo = worldExplo.end();
    for (; itExplo != endExplo; ++itExplo) {
        Explosion* updateBala = *itExplo;
        updateBala->Update();
    }
}

void Partida::cameraSetTransform() {

    int total = 0;
    float posX = 0;
    float posY = 0;

    float newSize = screenWidth;
    float minSize = screenWidth;

    float ratio = screenWidth / (float) screenHeight;
    float maxDifferenceX = 0;
    float maxDifferenceY = 0;

    //Posición
    for (int i = 0; i < worldPlayer.size(); i++) {
        if (!worldPlayer.at(i)->isPlayerDead()) {
            posX += worldPlayer.at(i)->getPosition().x;
            posY += worldPlayer.at(i)->getPosition().y;
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
    for (int i = 0; i < worldPlayer.size(); i++) {
        if (!worldPlayer.at(i)->isPlayerDead()) {
            float currentPosX = worldPlayer.at(i)->getPosition().x;
            if (abs(currentPosX - posX) > maxDifferenceX) maxDifferenceX = abs(currentPosX - posX);

            float currentPosY = worldPlayer.at(i)->getPosition().y;
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
    window->setView(*mainCamera);

}

void Partida::loadMap() {
    checkJoysticksConnected();
    
    Platform *suelo = new Platform(world, sf::Vector2f(screenWidth, 100.0), sf::Vector2f(screenWidth / 2, screenHeight), 0.2);
    worldPlatforms.push_back(suelo);

    Platform *paredIzda = new Platform(world, sf::Vector2f(100.0, screenHeight), sf::Vector2f(0, screenHeight / 2), 0);
    worldPlatforms.push_back(paredIzda);

    Platform *paredDcha = new Platform(world, sf::Vector2f(100.0, screenHeight), sf::Vector2f(screenWidth, screenHeight / 2), 0);
    worldPlatforms.push_back(paredDcha);

    Platform *platformDcha = new Platform(world, sf::Vector2f(120.0, 50.0), sf::Vector2f(screenWidth / 4, screenHeight / 3), 0.2);
    worldPlatforms.push_back(platformDcha);

    Platform *platformIzda = new Platform(world, sf::Vector2f(120.0, 50.0), sf::Vector2f(3 * screenWidth / 4, screenHeight / 3), 0.2);
    worldPlatforms.push_back(platformIzda);

    Platform *platformCentr = new Platform(world, sf::Vector2f(120.0, 50.0), sf::Vector2f(screenWidth / 2, 2 * screenHeight / 3), 0.2);
    worldPlatforms.push_back(platformCentr);

    Weapon *pistola1 = new Weapon(world, Vector2f(50, 30), sf::Vector2f(screenWidth / 4, (screenHeight / 3) - 5), 1.0f, 1, 10, 50, true, true);
    worldWeapons.push_back(pistola1);

    Weapon *pistola2 = new Weapon(world, Vector2f(50, 30), sf::Vector2f(3 * screenWidth / 4, (screenHeight / 3) - 5), 1.0f, 1, 10, 20, false, false);
    worldWeapons.push_back(pistola2);
}

Partida::~Partida() {
}