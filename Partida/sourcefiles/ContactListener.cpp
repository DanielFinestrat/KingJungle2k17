
/* 
 * File:   ContactListener.cpp
 * Author: daniel
 * 
 * Created on 26 de marzo de 2017, 20:41
 */

#include "../headerfiles/ContactListener.h"
#include "../headerfiles/Partida.h"

void ContactListener::BeginContact(b2Contact* contact) {

    Partida *partida = Partida::getInstance();

    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    Entidad* entidadA = static_cast<Entidad*> (bodyUserDataA);
    Entidad* entidadB = static_cast<Entidad*> (bodyUserDataB);

    //cout << "BOOM colision - " << entidadA->getTag() << " - " << entidadB->getTag() << endl;

    //Colision con Balas
    if (entidadA->getTag().compare("Bala") == 0 || entidadB->getTag().compare("Bala") == 0) {
        if (entidadA->getTag().compare("Bala") == 0) {
            Bala* bala = static_cast<Bala*> (bodyUserDataA);
            partida->bullets2Delete.insert(bala);
        } else if (entidadB->getTag().compare("Bala") == 0) {
            Bala* bala = static_cast<Bala*> (bodyUserDataB);
            partida->bullets2Delete.insert(bala);
        }
    }

    if (entidadA->getTag().compare("Player") == 0 || entidadB->getTag().compare("Player") == 0) {
        if (entidadA->getTag().compare("Bala") == 0) {
            Player* player = static_cast<Player*> (bodyUserDataA);
            player->die();
        } else if (entidadB->getTag().compare("Bala") == 0) {
            Player* player = static_cast<Player*> (bodyUserDataA);
            player->die();
        }
    }


}

//void ContactListener::EndContact(b2Contact* contact){}





