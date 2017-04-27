
/* 
 * File:   IAController.cpp
 * Author: angel
 * 
 * Created on 25 de abril de 2017, 14:12
 */

#include "../headerfiles/IAController.h"
#include "../headerfiles/Partida.h"

IAController::IAController(b2World *world) {
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

    player = new Player(*world);

    vector<int> position = partida->spawnPlayer.at(0);
    //Elimina el element de la primera posicion y la inserta en la última
    partida->spawnPlayer.erase(partida->spawnPlayer.begin());
    partida->spawnPlayer.push_back(position);

    player->setPosition(position.at(0), position.at(1));
    player->setColor(partida->worldPlayer.size());

    partida->worldPlayer.push_back(player);

    //cout << "He insertado un mando con la id " << this->id << " " << tipo << endl;
}

IAController::~IAController() {
}

void IAController::pressUpdateState(int pressedButton) {
    if (misBotones.at(0).numBoton == pressedButton && !misBotones.at(0).pulsado) {
        misBotones.at(0).pulsado = true;
        //cout << id << ".- He saltado" << endl;
        player->jump();
    } else if (misBotones.at(1).numBoton == pressedButton && !misBotones.at(1).pulsado) {
        misBotones.at(1).pulsado = true;
        //cout << id << ".- He disparado" << endl;
        player->shoot();
    } else if (misBotones.at(2).numBoton == pressedButton && !misBotones.at(2).pulsado) {
        misBotones.at(2).pulsado = true;
        //cout << id << ".- He interactuado" << endl;
        player->interact();
    } else if (misBotones.at(3).numBoton == pressedButton && !misBotones.at(3).pulsado) {
        misBotones.at(3).pulsado = true;
        //cout << id << ".- Me he burlado" << endl;
        player->mock();
    } else if (misBotones.at(4).numBoton == pressedButton && !misBotones.at(4).pulsado) {
        misBotones.at(4).pulsado = true;
        //cout << id << ".- He pausado" << endl;
        player->pause(true);
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
    if (ejeX != estadoEjeX) {
        //cout << "Me muevo en el eje X en la dirección " << ejeX << endl;
        estadoEjeX = ejeX;
        player->changeDirection(estadoEjeX);
    }
}

void IAController::checkAxisY(int ejeY) {
    if (ejeY > 10) ejeY = 1;
    else if (ejeY < -10) ejeY = -1;
    else ejeY = 0;

    //1 = agachado
    if (ejeY != estadoEjeY) {
        //cout << "Me muevo en el eje Y en la dirección " << ejeY << endl;
        estadoEjeY = ejeY;
        player->duck(estadoEjeY);
    }
}

int IAController::readTile(int layer) {
    int X = (int) (player->getPosition().x * PPM / 32); //32 = tamaño tile
    int Y = (int) (player->getPosition().y * PPM / 32);
    if (Y < 0) {
        Y = 0;
    }
    if (X < 0) {
        X = 0;
    }

    int lugar = Partida::getInstance()->_tilemap[layer][Y][X];
}

void IAController::interact() {
    if (estado.compare("buscarArma") == 0) {
        pressUpdateState(1);
        releaseUpdateState(1);
        estado = "matar";
    } else if (estado.compare("matar") == 0) {
        pressUpdateState(2);
        releaseUpdateState(2);
        if (!player->hasWeapon()) {
            estado = "buscarArma";
        } else if (player->getWeapon()->ammo <= 0) {
            pressUpdateState(1);
            releaseUpdateState(1);
        }
    }
}

void IAController::moveTo(float PosX, float PosY, float dist, Controlador* seguir) {
    cout << estado << endl;
    if (!player->isJumping()) {
        if (  (PosY > 0.9 && (seguir == NULL || !seguir->player->isJumping())) || dist>10   ) {
            cout << "superior" << endl;	
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

        }            //Jugador esta en misma altura (saltando o no)
        else if (PosY > -0.5 && PosY < 3.2) {
            //cout << "misma" << endl;
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
                if (PosX != 0) {
                    interact();
                    checkAxisX(0);
                } else {
                    checkAxisX(0);
                }
            }
        }            //Jugador esta en una altura inferior
        else if (PosY <= -0.5) {
            //cout << "inferior" << endl;
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
}

vector<float> IAController::buscarArma() {
    Partida* partida = Partida::getInstance();
    b2Vec2 IAposition = player->getPosition();
    float PosX = 0, PosY = 0;
    float distancia = -1;
    bool encontrada = false;

    for (int i = 0; i < partida->worldWeapons.size(); i++) {
        Weapon* arma = partida->worldWeapons.at(i);
        if (!arma->inPossession && arma->ammo > 0) {
            //cout << i << endl;
            b2Vec2 position = arma->m_pBody->GetPosition();
            float dist = sqrt(pow(IAposition.x - position.x, 2) + pow(IAposition.y - position.y, 2));
            if (distancia == -1) {
                encontrada = true;
                distancia = dist;
                PosX = IAposition.x - position.x;
                PosY = IAposition.y - position.y;
            } else if (dist < distancia) {
                distancia = dist;
                PosX = IAposition.x - position.x;
                PosY = IAposition.y - position.y;
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
    b2Vec2 IAposition = player->getPosition();
    float PosX = 0, PosY = 0;
    float distancia = -1;
    bool encontrada = false;

    for (int i = 0; i < partida->worldPlayer.size(); i++) {
        Player* player = partida->worldPlayer.at(i);
        if (i != id) {
            if (player->hasWeapon()) {
                b2Vec2 position = player->getPosition();
                float dist = sqrt(pow(IAposition.x - position.x, 2) + pow(IAposition.y - position.y, 2));
                if (distancia == -1) {
                    encontrada = true;
                    distancia = dist;
                    PosX = IAposition.x - position.x;
                    PosY = IAposition.y - position.y;
                } else if (dist < distancia) {
                    distancia = dist;
                    PosX = IAposition.x - position.x;
                    PosY = IAposition.y - position.y;
                }
            }
        }
    }

    for (int i = 0; i < partida->worldWeapons.size(); i++) {
        Weapon* weapon = partida->worldWeapons.at(i);
        if (!weapon->inPossession && weapon->ammo > 0) {
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

vector<float> IAController::buscarMatar() {



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
        float PosX = 0, PosY = 0;
        float distancia = -1;
        int ControladorSeguir = 0;

        b2Vec2 IAposition = player->getPosition();

        for (int i = 0; i < partida->worldPlayer.size(); i++) {
            Controlador* jugador = partida->worldControlador.at(i);
            if (i != id && !jugador->player->isPlayerDead()) { //Para probar la IA tiene id 0
                b2Vec2 position = jugador->player->getPosition();
                float dist = sqrt(pow(IAposition.x - position.x, 2) + pow(IAposition.y - position.y, 2));
                if (distancia == -1) {
                    ControladorSeguir = i;
                    distancia = dist;
                    PosX = IAposition.x - position.x;
                    PosY = IAposition.y - position.y;
                } else if (dist < distancia) {
                    ControladorSeguir = i;
                    distancia = dist;
                    PosX = IAposition.x - position.x;
                    PosY = IAposition.y - position.y;
                }
            }

        }
        //cout << PosX << " " << PosY << endl;
        pos.push_back(PosX);
        pos.push_back(PosY);
        pos.push_back(distancia);
        seguir = partida->worldControlador.at(ControladorSeguir);
        cout << ControladorSeguir << endl;
    }
    //Buscar zona para arriba
    moveTo(pos.at(0), pos.at(1), pos.at(2), seguir);
    //Juegador esta en zona superior y no saltando

}
