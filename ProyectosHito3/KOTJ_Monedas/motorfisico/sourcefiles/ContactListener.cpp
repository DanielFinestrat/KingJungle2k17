
/* 
 * File:   ContactListener.cpp
 * Author: daniel
 * 
 * Created on 26 de marzo de 2017, 20:41
 */

#include "../headerfiles/ContactListener.h"
#include "../../headerfiles/Partida.h"

void ContactListener::BeginContact(b2Contact* contact) {
	Partida *partida = Partida::getInstance();

	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
        
	Entidad* entidadA = static_cast<Entidad*> (bodyUserDataA);
	Entidad* entidadB = static_cast<Entidad*> (bodyUserDataB);
	string tagA = entidadA->getTag();
	string tagB = entidadB->getTag();


	
	entidadA->Contact(bodyUserDataB, tagB);
	entidadB->Contact(bodyUserDataA, tagA);
	
	// Player - Weapon - Bala - Explosion - Trampa
	//cout << "BOOM colision - " << entidadA->getTag() << " - " << entidadB->getTag() << endl;
/*
	//Colisión con Balas
	if (entidadA->getTag().compare("Bala") == 0 || entidadB->getTag().compare("Bala") == 0) {
		if (entidadA->getTag().compare("Bala") == 0) {
			Bala* bala = static_cast<Bala*> (bodyUserDataA);
			if (entidadB->getTag().compare("Player") == 0) {
				Player* player = static_cast<Player*> (bodyUserDataB);
			}

		} else if (entidadB->getTag().compare("Bala") == 0) {
			Bala* bala = static_cast<Bala*> (bodyUserDataB);

			if (entidadA->getTag().compare("Player") == 0) {
				Player* player = static_cast<Player*> (bodyUserDataA);
			}
		}
	}
        
        //Colisión con Explosiones
        else if (entidadA->getTag().compare("Explosion") == 0 || entidadB->getTag().compare("Explosion") == 0) {
		if (entidadA->getTag().compare("Explosion") == 0) {
			Explosion* explo = static_cast<Explosion*> (bodyUserDataA);
			if (entidadB->getTag().compare("Player") == 0) {
			}
		} else if (entidadB->getTag().compare("Explosion") == 0) {
			Explosion* explo = static_cast<Explosion*> (bodyUserDataB);
			if (entidadA->getTag().compare("Player") == 0) {
			}
		}
	}
        
        //Colisión con trampas
        else if (entidadA->getTag().compare("Trampa") == 0 || entidadB->getTag().compare("Trampa") == 0) {
		if (entidadA->getTag().compare("Trampa") == 0) {
			Trampa* trampa = static_cast<Trampa*> (bodyUserDataA);
			if (entidadB->getTag().compare("Player") == 0) {
                            Player* player = static_cast<Player*> (bodyUserDataB);
                            if(player->isPlayerDead() == false);
                                    //player->die(player->getDirMoving());
                                int dir = -1;
				if (trampa->cuerpo->getPosicionX() < player->getPositionX()) dir = 1;
				player->changeDirection(dir);
				partida->players2Delete.push_back(player);
                                
			}
		} else if (entidadB->getTag().compare("Trampa") == 0) {
			Trampa* trampa = static_cast<Trampa*> (bodyUserDataB);
			if (entidadA->getTag().compare("Player") == 0) {
				Player* player = static_cast<Player*> (bodyUserDataA);
                                if(player->isPlayerDead() == false);
                                
                                    //player->die(player->getDirMoving());
                                int dir = -1;
				if (trampa->cuerpo->getPosicionX() < player->getPositionX()) dir = 1;
				player->changeDirection(dir);
				partida->players2Delete.push_back(player);
			}
		}
	}*/
}





