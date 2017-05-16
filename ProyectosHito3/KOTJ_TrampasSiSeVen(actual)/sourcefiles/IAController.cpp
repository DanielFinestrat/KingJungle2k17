
/* 
 * File:   IAController.cpp
 * Author: angel
 * 
 * Created on 25 de abril de 2017, 14:12
 */

#include "../headerfiles/IAController.h"
#include "../headerfiles/Partida.h"

IAController::IAController() {
    tipo = "IA";
    estado = "buscarArma";

    Partida* partida = Partida::getInstance();

    boton b1;
    b1.nombre = "Salto"; //UP
    b1.numBoton = 0;
    b1.pulsado = false;
    misBotones.push_back(b1);

    boton b2;
    b1.nombre = "Disparo"; //R
    b2.numBoton = 2;
    b2.pulsado = false;
    misBotones.push_back(b2);

    boton b3;
    b1.nombre = "Interactuar"; //E
    b3.numBoton = 1;
    b3.pulsado = false;
    misBotones.push_back(b3);

    boton b4;
    b1.nombre = "Burlarse"; //W
    b4.numBoton = 3;
    b4.pulsado = false;
    misBotones.push_back(b4);

    boton b5;
    b1.nombre = "Pausar"; //Q
    b5.numBoton = 7;
    b5.pulsado = false;
    misBotones.push_back(b5);

    estadoEjeX = 0;
    estadoEjeY = 0;

    id = partida->worldPlayer.size();

    player = new Player();

    vector<int> position = partida->mapa->getSpawnPlayer().at(0);
    partida->mapa->spawnPlayer.erase(partida->mapa->spawnPlayer.begin());
    partida->mapa->spawnPlayer.push_back(position);

    player->setPosition(position.at(0), position.at(1));
    player->setColor(partida->worldPlayer.size());

    partida->worldPlayer.push_back(player);
    Hud::getInstance()->addPlayer(player);
}

IAController::~IAController() {
}

void IAController::pressUpdateState(int pressedButton) {
    if (misBotones.at(0).numBoton == pressedButton && !misBotones.at(0).pulsado) {
        misBotones.at(0).pulsado = true;
        player->jump();
    } else if (misBotones.at(1).numBoton == pressedButton && !misBotones.at(1).pulsado) {
        misBotones.at(1).pulsado = true;
        player->shoot();
    } else if (misBotones.at(2).numBoton == pressedButton && !misBotones.at(2).pulsado) {
        misBotones.at(2).pulsado = true;
        player->interact();
    } else if (misBotones.at(3).numBoton == pressedButton && !misBotones.at(3).pulsado) {
        misBotones.at(3).pulsado = true;
        player->mock();
    } else if (misBotones.at(4).numBoton == pressedButton && !misBotones.at(4).pulsado) {
        misBotones.at(4).pulsado = true;
        player->pause();
    }
}

void IAController::releaseUpdateState(int releasedButton) {
    if (misBotones.at(0).numBoton == releasedButton) {
        misBotones.at(0).pulsado = false;
        player->updateCanJumpStateState();
    } else if (misBotones.at(1).numBoton == releasedButton) {
        misBotones.at(1).pulsado = false;
    } else if (misBotones.at(2).numBoton == releasedButton) {
        misBotones.at(2).pulsado = false;
    } else if (misBotones.at(3).numBoton == releasedButton) {
        misBotones.at(3).pulsado = false;
    } else if (misBotones.at(4).numBoton == releasedButton) {
        misBotones.at(4).pulsado = false;
    }
}

void IAController::checkAxisX(int ejeX) {
    if (ejeX > 10) ejeX = 1;
    else if (ejeX < -10) ejeX = -1;
    else ejeX = 0;

    //1 = derecha

        estadoEjeX = ejeX;
        player->changeDirection(estadoEjeX);
    
}

void IAController::checkAxisY(int ejeY) {
    if (ejeY > 10) ejeY = 1;
    else if (ejeY < -10) ejeY = -1;
    else ejeY = 0;

    //1 = agachado
    if (ejeY != estadoEjeY) {
        estadoEjeY = ejeY;
        player->duck(estadoEjeY);
    }
}





int IAController::readTile(int layer) {
    int X = (int) (player->getPositionX() * PPM / 32);
    int Y = (int) (player->getPositionY() * PPM / 32);
    int maxX = Partida::getInstance()->mapa->xTiles;
    int maxY = Partida::getInstance()->mapa->yTiles;

    if (Y < 0) Y = 0;
    if (X < 0) X = 0;
    if (Y > maxY) Y = maxY;
    if (X > maxX) X = maxX;

    int lugar = Partida::getInstance()->mapa->_tilemap[layer][Y][X];
    return (lugar);
}

bool IAController::disparar(float dist, float PosX){
    bool disparo = false;
   
    //Compruebo que el jugador tenga una arma y que el arma este a rango de disparo
    if(player->hasWeapon() && dist < player->getWeapon()->getRango()){
        
        disparo = true;             //Si que se realiza el disparo
        checkAxisX(0);              //Se queda quito al disparar
        
        //Se cambia la dirección del jugador para que mire hacia el personaje
        if(PosX>=0){
            player->changeDirection(-1);
            player->changeDirection(0);
        }else{
            player->changeDirection(1);
            player->changeDirection(0);
        }
        
        pressUpdateState(2);        //Pulsa el botón de disparo
        releaseUpdateState(2);      //Suelta el botón de disparo
        
        
        //En el caso de que el jugador no tenga balas suelta el arma
        if (player->getWeapon()->ammo == 0) {
            pressUpdateState(1);
            releaseUpdateState(1);
        }
    }
    //En el caso de que el jugador no tenga arma este cambia su estado a buscarArma
    else if(!player->hasWeapon()){
        estado = "buscarArma";
    }
    
    return disparo;
}

void IAController::interact() {
    if (estado.compare("buscarArma") == 0) {
        pressUpdateState(1);
        releaseUpdateState(1);
        if(player->hasWeapon()){
            estado = "matar";
        }
    }
}

void IAController::moveTo(float PosX, float PosY, float dist, Controlador* seguir) {
    cout << estado << " " << dist<< " ";
    if (!player->isJumping()) {
        if ((PosY > 0.9 && (seguir == NULL || !seguir->player->isJumping())) ) {
		//if (PosY > 0.9 ) {
            cout << "superior";
            int lugar = readTile(layerSubir);
            int dir = 0;
            switch (lugar) {
                case 915:
                    checkAxisX(-100);
                    break;
                case 914:
                    checkAxisX(100);
                    break;
                case 917:
                    pressUpdateState(0);
                    releaseUpdateState(0);
                    checkAxisX(-100);
                    break;
                case 920:
                    pressUpdateState(0);
                    releaseUpdateState(0);
                    checkAxisX(100);
                    break;
                case 924:
                    checkAxisX(0);
                    break;
            }

        }//Jugador esta en misma altura (saltando o no)
        else if (PosY > -0.5 && PosY < 3.2) {
			cout << "misma";
            int lugar = readTile(layerSubir);
            switch (lugar) {
                case 917:
                    pressUpdateState(0);
                    releaseUpdateState(0);
                    break;
                case 920:
                    pressUpdateState(0);
                    releaseUpdateState(0);
                    break;
            }
            if (estado.compare("buscarArma") == 0) {
                if (PosX > 0.5) {
                    checkAxisX(-100);
                } else if (PosX<-0.5) {
                    checkAxisX(100);
                } else {
                    //Ha llegado a su destino
                    checkAxisX(0);
                    interact();
                }
            } else if (estado.compare("matar") == 0) {
                if(seguir == NULL || !disparar(dist, PosX)){
                    if (PosX > 0.5) {
                        checkAxisX(-100);
                    } else if (PosX<-0.5) {
                        checkAxisX(100);
                    }
                }
            }
        }//Jugador esta en una altura inferior
        else if (PosY <= -0.5) {
            cout << "inferior";
            int lugar = readTile(layerBajar);
            int dir = 0;
            switch (lugar) {
                case 915:
                    checkAxisX(-100);
                    break;
                case 914:
                    checkAxisX(100);
                    break;
                case 917:
                    pressUpdateState(0);
                    releaseUpdateState(0);
                    checkAxisX(-100);
                    break;
                case 920:
                    pressUpdateState(0);
                    releaseUpdateState(0);
                    checkAxisX(100);
                    break;
                case 922:
                    dir = 0;
                    if (PosX > 1) {
                        dir = -100;
                    } else if (PosX<-1) {
                        dir = 100;
                    }
                    checkAxisX(dir);
                    break;
            }
        }
    }
	cout << endl;
}

vector<float> IAController::buscarArma() {
    Partida* partida = Partida::getInstance();
    float IApositionX = player->getPositionX();
    float IApositionY = player->getPositionY();
    float PosX = 0, PosY = 0;
    float distancia = -1;
    bool encontrada = false;

    for (int i = 0; i < partida->worldWeapons.size(); i++) {
        if (partida->worldWeapons.at(i) != NULL) {
            Weapon* arma = partida->worldWeapons.at(i);
            if (!arma->inPossession && arma->ammo != 0) {
                //cout << i << endl;
                float positionX = arma->cuerpo->getPosicionX();
                float positionY = arma->cuerpo->getPosicionY();
                float dist = sqrt(pow(IApositionX - positionX, 2) + pow(IApositionY - positionY, 2));
                if (distancia == -1) {
                    encontrada = true;
                    distancia = dist;
                    PosX = IApositionX - positionX;
                    PosY = IApositionY - positionY;
                } else if (dist < distancia) {
                    distancia = dist;
                    PosX = IApositionX - positionX;
                    PosY = IApositionY - positionY;
                }
            }
        }
    }
    if (!encontrada) {
        estado = "huir";
    }
    vector<float> ret;
    ret.push_back(PosX);
    ret.push_back(PosY);
    ret.push_back(distancia);
    return ret;
}

vector<float> IAController::buscarHuida() {
    Partida* partida = Partida::getInstance();
    float IApositionX = player->getPositionX();
    float IApositionY = player->getPositionY();
    float PosX = 0, PosY = 0;
    float distancia = -1;
    bool encontrada = false;

    for (int i = 0; i < partida->worldPlayer.size(); i++) {
        Player* player = partida->worldPlayer.at(i);
        if (i != id) {
            if (player->hasWeapon()) {
                Weapon* arma = player->getWeapon();
                float positionX = arma->cuerpo->getPosicionX();
                float positionY = arma->cuerpo->getPosicionY();
                float dist = sqrt(pow(IApositionX - positionX, 2) + pow(IApositionY - positionY, 2));
                if (distancia == -1) {
                    encontrada = true;
                    distancia = dist;
                    PosX = IApositionX - positionX;
                    PosY = IApositionY - positionY;
                } else if (dist < distancia) {
                    distancia = dist;
                    PosX = IApositionX - positionX;
                    PosY = IApositionY - positionY;
                }
            }
        }
    }

    for (int i = 0; i < partida->worldWeapons.size(); i++) {
        Weapon* weapon = partida->worldWeapons.at(i);
        if (!weapon->inPossession && weapon->ammo != 0) {
            estado = "buscarArma";
        }
    }

    if (PosX > 0) {
        PosX = 0;
    } else {
        PosX = 0;
    }

    if (PosY > 0) {
        PosY = -10;
    } else {
        PosY = 10;
    }

    vector<float> ret;
    ret.push_back(PosX);
    ret.push_back(PosY);
    ret.push_back(distancia);
    return ret;

}

vector<float> IAController::buscarMatar(Controlador** seguir) {
    Partida* partida = Partida::getInstance();
    float PosX = 0, PosY = 0;
    float distancia = -1;
    int ControladorSeguir = 0;

    float IApositionX = player->getPositionX();
    float IApositionY = player->getPositionY();

    for (int i = 0; i < partida->worldPlayer.size(); i++) {
        Controlador* jugador = partida->worldControlador.at(i);
        if (i != id && !jugador->player->isPlayerDead()) { //Para probar la IA tiene id 0
            float positionX = jugador->player->getPositionX();
            float positionY = jugador->player->getPositionY();
            float dist = sqrt(pow(IApositionX - positionX, 2) + pow(IApositionY - positionY, 2));
            if (distancia == -1) {
                ControladorSeguir = i;
                distancia = dist;
                PosX = IApositionX - positionX;
                PosY = IApositionY - positionY;
            } else if (dist < distancia) {
                ControladorSeguir = i;
                distancia = dist;
                PosX = IApositionX - positionX;
                PosY = IApositionY - positionY;
            }
        }

    }
    if (partida->worldControlador.at(ControladorSeguir) != NULL) {
        *seguir = partida->worldControlador.at(ControladorSeguir);
    }
    
	if(!player->hasWeapon()){
        estado = "buscarArma";
    }
	
    vector<float> ret;
    ret.push_back(PosX);
    ret.push_back(PosY);
    ret.push_back(distancia);
    return ret;
}

void IAController::update() {
    //MIRAR DE HACER 3 CAPAS DE TILED. UNA PARA SUBIR, OTRA PARA BAJAR Y OTRA PARA SEGUI
    //Método de seguir persona

    Partida* partida = Partida::getInstance();

    vector<float> pos;
    Controlador* seguir = NULL;

    if (estado.compare("buscarArma") == 0) {
        pos = buscarArma();
    } else if (estado.compare("huir") == 0) {
        pos = buscarHuida();
    } else if (estado.compare("matar") == 0) {
        pos = buscarMatar(&seguir);
    }
	
	cout << pos.at(2) << endl;
	
    moveTo(pos.at(0), pos.at(1), pos.at(2), seguir);

}