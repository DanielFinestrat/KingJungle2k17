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

    console = Console();
}

Partida::Partida(const Partida& orig) {
}

Partida* Partida::getInstance() {
    if (instance == NULL) instance = new Partida();
    return (instance);
}
/*
void Partida::IA(){
	
	//MIRAR DE HACER 3 CAPAS DE TILED. UNA PARA SUBIR, OTRA PARA BAJAR Y OTRA PARA SEGUI
	
	//Método de seguir persona
	float PosX = 0, PosY = 0;
	float distancia = -1;
	int ControladorSeguir = 0;

	Controlador* IA = worldControlador.at(0);
	b2Vec2 IAposition = IA->player->getPosition();
	
	for(int i=0; i<worldPlayer.size(); i++){
		Controlador* jugador = worldControlador.at(i);
		if(i!=0){	//Para probar la IA tiene id 0
			b2Vec2 position = jugador->player->getPosition();
			float dist = sqrt(pow(IAposition.x - position.x, 2) + pow(IAposition.y - position.y, 2));
			if(distancia == -1){
				//cout << "hi" << dist<< endl;
				ControladorSeguir = i;
				distancia = dist;
				PosX = IAposition.x - position.x;
				PosY = IAposition.y - position.y;
			}
			else if(dist < distancia){
				//cout << "hey" << dist <<  endl;
				ControladorSeguir = i;
				distancia = dist;
				PosX = IAposition.x - position.x;
				PosY = IAposition.y - position.y;
			}
		}
	}
	//cout << PosX << " " << PosY << endl;
	
	//Buscar zona para arriba
	Controlador* seguir = worldControlador.at(ControladorSeguir);
	
	//Juegador esta en zona superior y no saltando
	cout << IA->player->isJumping() << endl;
	if(!IA->player->isJumping()){
		if( (PosY>0.9 && !seguir->player->isJumping())){
			cout << "superior" << endl;


			int X = (int) (IA->player->getPosition().x*PPM / 32); //32 = tamaño tile
			int Y = (int) (IA->player->getPosition().y*PPM / 32);
			if(Y<0)Y=0;
			int lugar = _tilemap[3][Y][X];
			int dir = 0;
			switch(lugar){
				case 915: 
					IA->checkAxisX(-100);
					break;
				case 914:
					IA->checkAxisX(100);
					break;
				case 917:
					IA->pressUpdateState(0);
					IA->releaseUpdateState(0);
					IA->checkAxisX(-100);
					break;
				case 920:
					IA->pressUpdateState(0);
					IA->releaseUpdateState(0);
					IA->checkAxisX(100);
					break;
			}	

		}
		//Jugador esta en misma altura (saltando o no)
		else if(PosY > -0.5 && PosY<3.2){
			cout << "misma" << endl;


			int dir = 0;
			if(PosX>1){dir = -100;}else if(PosX<-1){dir = 100;}
			IA->checkAxisX(dir);
		}
		//Jugador esta en una altura inferior
		else if(PosY <=-0.5){
			cout << "inferior" << endl;

			int X = (int) (IA->player->getPosition().x*PPM / 32); //32 = tamaño tile
			int Y = (int) (IA->player->getPosition().y*PPM / 32);
			if(Y<0)Y=0;
			int lugar = _tilemap[1][Y][X];
			int dir = 0;
			switch(lugar){
				case 915: 
					IA->checkAxisX(-100);
					break;
				case 914:
					IA->checkAxisX(100);
					break;
				case 917:
					IA->pressUpdateState(0);
					IA->releaseUpdateState(0);
					IA->checkAxisX(-100);
					break;
				case 920:
					IA->pressUpdateState(0);
					IA->releaseUpdateState(0);
					IA->checkAxisX(100);
					break;
				case 922:
					dir = 0;
					if(PosX>1){dir = -100;}else if(PosX<-1){dir = 100;}
					IA->checkAxisX(dir);
					break;	
			}	
		}
	}
		
}
*/

void Partida::Input() {

	for(int i=0; i<worldControlador.size(); i++){
		Controlador* c = worldControlador.at(i);
		if(c->tipo.compare("IA")==0){
			c->update();
		}
	}
	
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
					case Keyboard::F3:
						addPlayerIA();
						break;
                    case Keyboard::Tab:
                        console.toggleConsole();
                        break;

                    case Keyboard::Return:
                        console.send();
                        break;

                    case Keyboard::BackSpace:
                        console.deleteChar();
                        break;
                }
                break;

            case Event::KeyReleased:
                if (usingKeyboard) worldControlador.at(findKeyboardControlador())->releaseUpdateState(event.key.code);
                break;

            case sf::Event::TextEntered:
                console.write(event);
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
    //drawPlatforms();
    drawPlayers();
    drawWeapons();
    drawBullets();
    drawExplo();
    drawMap();
    window->setView(*hudCamera);
    temporizador->Draw(window);
    console.draw(window);
    window->display();

}

void Partida::drawMap() {

    for (int i = 0; i < map_sprites.size(); i++) {

        window->draw(*map_sprites.at(i));

    }

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
    /*addPlayerJoystick(&playerJoysticks, 1);
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
        if (worldControlador.at(i)->tipo.compare("JoyStick") == 0 && worldControlador.at(i)->id == id) add = false;
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

void Partida::addPlayerIA(){
	if(worldControlador.size() < 4){
		worldControlador.push_back(new IAController(world));
	}
}

void Partida::respawn() {
    for (int i = 0; i < worldPlayer.size(); i++) {
        Player* player = worldPlayer.at(i);
			
		vector<int> position = spawnPlayer.at(0);
		//Elimina el element de la primera posicion y la inserta en la última
		spawnPlayer.erase(spawnPlayer.begin());
		spawnPlayer.push_back(position);
	
		player->setPosition(position.at(0), position.at(1));
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
	cargarXML();
    checkJoysticksConnected();
	/*
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
*/
    Weapon *pistola1 = new Weapon(world, Vector2f(50, 30), sf::Vector2f(screenWidth / 4, (screenHeight / 3) - 5), 1.0f, 1, 10, 50, true, true);
    worldWeapons.push_back(pistola1);

    Weapon *pistola2 = new Weapon(world, Vector2f(50, 30), sf::Vector2f(3 * screenWidth / 4, (screenHeight / 3) - 5), 1.0f, 1, 10, 20, false, false);
    worldWeapons.push_back(pistola2);
}

void Partida::cargarTiles(int capa, int y, int x) {

    if (!map_texture.loadFromFile("resources/sprites/tilesheet.png")) {

        cout << "Failed to load tilesheet!" << endl;

    }

    for (int j = 0; j < y; j++) {

        for (int k = 0; k < x; k++) {

            int miTile = _tilemap[0][j][k];

            if (miTile != 0) {

                //cout<<y<<endl;

                int ancho = (miTile % 44)-1;

                int altura = (miTile / 44);

                IntRect *myRect = new IntRect(ancho * 32, altura * 32, 32, 32);

                sf::Sprite *newTile = new Sprite();

                newTile->setTexture(map_texture);

                newTile->setTextureRect(*myRect);

                newTile->setPosition(k*32, j*32);

                map_sprites.push_back(newTile);

            }

        }

    }

}

void Partida::guardarCapas(TiXmlElement* map){
	int _width = 0; 
	int _height = 0;
	int _numLayers = 0;

	//Leemos el valor de X e Y del mapa
	map->QueryIntAttribute("width", &_width);
	map->QueryIntAttribute("height", &_height);
	
	//Leemos el número de layers que hay
	TiXmlElement* layer = map->FirstChildElement("layer");
	while(layer){
		_numLayers++;
		layer = layer->NextSiblingElement("layer");
	}
	
	//Creamos la matriz donde irá la información
	_tilemap = new int**[_numLayers];
	for(int i=0; i<_numLayers; i++){
		_tilemap[i] = new int*[_height];
		for(int j=0; j<_height; j++){
			_tilemap[i][j] = new int[_width];
			for(int k=0; k<_width; k++){
				_tilemap[i][j][k] = 0;
			}
		}
	}

	cout << "altura: " << _height << " - ancho: " << _width << " - capas: " << _numLayers << endl;
	
	//Leemos las matrices
	TiXmlElement *tile;
	layer = map->FirstChildElement("layer");
	tile = layer->FirstChildElement("data")->FirstChildElement("tile");
	
		 
	for(int l=0; l<_numLayers; l++){
		if(l!=0){
			layer = layer->NextSiblingElement("layer");
			tile = layer->FirstChildElement("data")->FirstChildElement("tile");
		}
		for(int y=0; y<_height; y++){
			for(int x = 0; x < _width; x++){
				tile->QueryIntAttribute("gid", &_tilemap[l][y][x]);
				//Avanzo al siguiente tag
				tile = tile->NextSiblingElement("tile");
			}
		}
		
	}
	cargarTiles(_numLayers, _height, _width);
}

void Partida::guardarObj(TiXmlElement* map){
	int _numLayers = 0;
	
	//Leemos el número de layers que hay
	TiXmlElement* layer = map->FirstChildElement("objectgroup");
	while(layer){
		_numLayers++;
		layer = layer->NextSiblingElement("objectgroup");
	}
	
	//Leemos las matrices
	TiXmlElement *object;
	TiXmlElement *rozamiento;
	layer = map->FirstChildElement("objectgroup");
	object = layer->FirstChildElement("object");
	
	int _width = 0;
	int _height = 0;
	int _sizeX = 0;
	int _sizeY = 0;
	string tipo;
	
	for(int l=0; l<_numLayers; l++){
		if(l!=0){
			layer = layer->NextSiblingElement("objectgroup");
			object = layer->FirstChildElement("object");
		}
		while(object){
			tipo = object->Attribute("name");
			//cout << tipo << endl;
			if(tipo.compare("platform") == 0){
				int _roz;
				rozamiento = object->FirstChildElement("properties")->FirstChildElement("property");
				object->QueryIntAttribute("x", &_width);
				object->QueryIntAttribute("y", &_height);
				object->QueryIntAttribute("width", &_sizeX);
				object->QueryIntAttribute("height", &_sizeY);
				
				
				rozamiento->QueryIntAttribute("value", &_roz);
				//cout << _width << " " << _height << " " << _sizeX << " " << _sizeY << endl;
				Platform *suelo = new Platform(world, sf::Vector2f((float)_sizeX, (float)_sizeY), sf::Vector2f((float)_width + _sizeX/2, (float)_height + _sizeY/2), ((float)_roz)/10.0);
				worldPlatforms.push_back(suelo);
			}
			else if(tipo.compare("player") == 0){
				object->QueryIntAttribute("x", &_width);
				object->QueryIntAttribute("y", &_height);
				vector<int> posicion;
				posicion.push_back(_width);
				posicion.push_back(_height);
				spawnPlayer.push_back(posicion);
				//cout << _width << " " << _height << endl;
			}
			object = object->NextSiblingElement("object");
		}
	}
	
}

void Partida::cargarXML(){

	TiXmlDocument doc("resources/mapas/mapa.tmx");
	doc.LoadFile();

	TiXmlElement* map = doc.FirstChildElement("map");
	guardarCapas(map);
	guardarObj(map);
	
}

Partida::~Partida() {
}