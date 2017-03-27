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
    window = new RenderWindow(VideoMode(screenWidth, screenHeight), "KingOfTheJungle 2k17 Turbo Power Edition");
    window->setFramerateLimit(60);
    world = new b2World(b2Vec2(0.0f, 9.8f));
    world->SetContactListener(&myContactListener);
    checkJoysticksConnected();
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
                addPlayerJoystick(&playerJoysticks, event.joystickConnect.joystickId);
                break;

            case Event::JoystickMoved:
                if (event.joystickMove.axis == Joystick::X) {
                    playerJoysticks.at(findJoystickWithId(&playerJoysticks, event.joystickMove.joystickId)).checkAxisX(event.joystickMove.position);
                }
                if (event.joystickMove.axis == Joystick::Y) {
                    playerJoysticks.at(findJoystickWithId(&playerJoysticks, event.joystickMove.joystickId)).checkAxisY(event.joystickMove.position);
                }
                break;

            case Event::JoystickButtonPressed:
                playerJoysticks.at(findJoystickWithId(&playerJoysticks, event.joystickButton.joystickId)).pressUpdateState(event.joystickButton.button);
                break;

            case Event::JoystickButtonReleased:
                playerJoysticks.at(findJoystickWithId(&playerJoysticks, event.joystickButton.joystickId)).releaseUpdateState(event.joystickButton.button);
                break;
				
				
			case Event::KeyPressed:
				respawn();
				break;
        }
    }

}

void Partida::erasePlayers(){
	for(int i=0; i < players2Delete.size(); i++){
		
		players2Delete.at(i)->die(players2Delete.at(i)->getDirMoving());
	}
	players2Delete.clear();
}

void Partida::eraseBullets() {
    set<Bala*>::iterator itBala = bullets2Delete.begin();

    for (; itBala !=  bullets2Delete.end(); ++itBala) {
        Bala* dyingBala = *itBala;
        /* if (dyingBala->explosion == true) {
             b2Vec2 position = dyingBala->m_pBody->GetPosition();

             Explosion *nueva;
             nueva = new Explosion(dyingBala->m_pBody->GetWorld(), sf::Vector2f(position.x * PPM, position.y * PPM), 1.0f, 0.05f, 0.5f);
             listadoExplosion.insert(nueva);
         }*/
        worldBullets.erase(dyingBala);
        bullets2Delete.erase(dyingBala);
        delete dyingBala;
        dyingBala = NULL;
    }
    bullets2Delete.clear();
}

void Partida::Erase() {
    eraseBullets();
	erasePlayers();
}

void Partida::Update() {
    world->Step(TIMESTEP, VELITER, POSITER);
    Time frameTime = frameClock.restart();
    updateWeapons();
    updatePlayers(frameTime, &playerJoysticks);
    updateBullets();
}

void Partida::Render() {
    window->clear(sf::Color::Black);
    drawPlatforms();
    drawPlayers();
    drawWeapons();
    drawBullets();
    window->display();
}

void Partida::drawPlatforms() {
    for (int i = 0; i < worldPlatforms.size(); i++) {
        worldPlatforms.at(i)->Render(window);
    }
}

void Partida::drawPlayers() {
    for (int i = 0; i < playerJoysticks.size(); i++) {
        window->draw(playerJoysticks.at(i).player->getPlayerSprite());
    }
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

int Partida::findJoystickWithId(vector<PlayerJoystick> *playerJoysticks, int id) {
    int index = -1;

    for (int i = 0; i < playerJoysticks->size() && index == -1; i++) {
        if (playerJoysticks->at(i).id == id) index = i;
    }

    return index;
}

void Partida::checkJoysticksConnected() {
    Joystick joystickManager;
    for (int i = 0; i < 4; i++) {
        if (joystickManager.isConnected(i)) {
            addPlayerJoystick(&playerJoysticks, i);
        }
    }
}

void Partida::addPlayerJoystick(vector<PlayerJoystick> *playerJoysticks, int id) {
    //Para saber si la tenemos que añador
    bool add = true;

    //Comprobamos si existe el mando y actualizamos la condición
    for (int i = 0; i < playerJoysticks->size() && add; i++) {
        if (playerJoysticks->at(i).id == id) add = false;
    }

    //Añadimos en funcion de la condición
    if (add) {
        PlayerJoystick p(id, world);
        playerJoysticks->push_back(p);
        PlayerJoystick p1(id + 1, world);
        playerJoysticks->push_back(p1);
        PlayerJoystick p2(id + 5, world);
        playerJoysticks->push_back(p2);
        PlayerJoystick p3(id + 9, world);
        playerJoysticks->push_back(p3);
    }
}

void Partida::respawn(){
	for(int i = 0; i < playerJoysticks.size(); i++){
		if(playerJoysticks.at(i).player!=NULL)
			playerJoysticks.at(i).player->respawn();
	}
}

void Partida::updatePlayers(Time frameTime, vector<PlayerJoystick> *playerJoysticks) {
    for (int i = 0; i < playerJoysticks->size(); i++) {
        playerJoysticks->at(i).player->update(frameTime);
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

void Partida::loadMap() {
    Platform *suelo = new Platform(world, sf::Vector2f(screenWidth, 100.0), sf::Vector2f(screenWidth / 2, screenHeight), 0.2);
    worldPlatforms.push_back(suelo);

    Platform *paredIzda = new Platform(world, sf::Vector2f(100.0, screenHeight), sf::Vector2f(0, screenHeight / 2), 0);
    worldPlatforms.push_back(paredIzda);

    Platform *paredDcha = new Platform(world, sf::Vector2f(100.0, screenHeight), sf::Vector2f(screenWidth, screenHeight / 2), 0);
    worldPlatforms.push_back(paredDcha);

    Weapon *pistola1 = new Weapon(world, Vector2f(50, 30), Vector2f(screenWidth / 4, 200), 1.0f, 1, 10, 20);
    worldWeapons.push_back(pistola1);

    Weapon *pistola2 = new Weapon(world, Vector2f(50, 30), Vector2f(screenWidth / 4.5, 200), 1.0f, 1, 10, 30);
    worldWeapons.push_back(pistola2);
}

Partida::~Partida() {
}