
/* 
 * File:   Player.cpp
 * Author: amygwyllion
 * 
 * Created on 21 de marzo de 2017, 8:00
 */

#include "headerfiles/Player.h"
#include "headerfiles/Partida.h"
#include "motorgrafico/headerfiles/Motorgrafico.h"
#include <iostream>

Player::Player() {
    tag = "Player";

    //Creamos los diferentes frames que va a tener nuestro sprite animado
    walkingAnimation.setSpriteSheet(Resources::getInstance()->getTexture(Resources::getInstance()->sprites));
    walkingAnimation.addFrame(IntRect(3, 142, 49 - 3, 207 - 149));
    walkingAnimation.addFrame(IntRect(52, 142, 97 - 52, 207 - 143));
    walkingAnimation.addFrame(IntRect(151, 142, 196 - 151, 207 - 143));
    walkingAnimation.addFrame(IntRect(199, 142, 243 - 199, 207 - 143));
    walkingAnimation.addFrame(IntRect(293, 142, 339 - 293, 207 - 143));
    walkingAnimation.addFrame(IntRect(149, 142, 196 - 149, 207 - 143));

    jumpAnimation.setSpriteSheet(Resources::getInstance()->getTexture(Resources::getInstance()->sprites));
    jumpAnimation.addFrame(IntRect(53, 219, 98 - 53, 70));
    jumpAnimation.addFrame(IntRect(101, 289 - 70, 146 - 101, 70));

    fallAnimation.setSpriteSheet(Resources::getInstance()->getTexture(Resources::getInstance()->sprites));
    fallAnimation.addFrame(IntRect(306, 285 - 70, 351 - 306, 70));
    fallAnimation.addFrame(IntRect(354, 285 - 70, 399 - 354, 70));

    standAnimation.setSpriteSheet(Resources::getInstance()->getTexture(Resources::getInstance()->sprites));
    standAnimation.addFrame(IntRect(4, 0, 38 - 4, 67));
    standAnimation.addFrame(IntRect(41, 0, 74 - 41, 67));
    standAnimation.addFrame(IntRect(77, 0, 110 - 77, 67));

    duckAnimation.setSpriteSheet(Resources::getInstance()->getTexture(Resources::getInstance()->sprites));
    duckAnimation.addFrame(IntRect(3, 298 - 70, 51 - 3, 70));

    deadAnimation.setSpriteSheet(Resources::getInstance()->getTexture(Resources::getInstance()->sprites));
    deadAnimation.addFrame(IntRect(3, 1470, 77 - 3, 1540 - 1470));

    currentAnimation = &standAnimation; //Establecemos la animacion por defecto
    playerSprite = new SpriteAnimated(seconds(0.1), true, false); //Creamos un sprite animado
    playerSprite->setOrigin(pSize / 2, pSize / 2);

    dirMoving = 0;
    dirLooking = 1;

    isDucking = false;
    isDead = false;
    paused = false;

    canJump = true;
    updateCanJumpState = false;
    fuerzaSalto = -50;
    fuerzaMovimiento = 5;
    velocidadMaxima = 1;

    cuerpo = Motorfisico::getInstance()->crearCuerpo(0, 0, pSize / 2, pSize, this);
    cuerpo->setMaskBits(MASK_PLAYER);
    cuerpo->setCategoryBits(CATEGORY_PLAYER);
    cuerpo->setDensity(0.75f);

    weapon = NULL;
    points = 0;

    monedero = 0;
    decreasedCoins = 0;

    coinsClock = new InnerClock();
    coinsClock->restartClock();

    respawnClock = new InnerClock();
    respawnClock->restartClock();

    coinsTime = 0;
    respawnTime = 0;

}

Player::~Player() {
}

void Player::setStandAnimation() {
    currentAnimation = &standAnimation;
}

void Player::setWalkingAnimation() {
    currentAnimation = &walkingAnimation;
}

void Player::setJumpAnimation() {
    currentAnimation = &jumpAnimation;
}

void Player::setFallAnimation() {
    currentAnimation = &fallAnimation;
}

void Player::setDuckAnimation() {
    currentAnimation = &duckAnimation;
}

void Player::setDeadAnimation() {
    currentAnimation = &deadAnimation;
}

void Player::playAnimation() {
    playerSprite->play(*currentAnimation);
}

Animation* Player::getCurrentAnimation() {
    return currentAnimation;
}

void Player::eraseBody() {

    float velx = cuerpo->getVelocidadX();
    float vely = cuerpo->getVelocidadY();

    if (fabs(velx) < 0.005 && fabs(vely) < 0.005) {
        cuerpo->setActive(false);
    }
}

void Player::update(Time frameTime) {
    playerSprite->update(frameTime);

    float posx = cuerpo->getPosicionX();
    float posy = cuerpo->getPosicionY();

    move();

    if (!canJump && updateCanJumpState) canJump = isGrounded();

    if (isDead) {
        setDeadAnimation();
        if (cuerpo->getActive()) eraseBody();
    } else if ((int) cuerpo->getVelocidadY() > 0) setFallAnimation();

    else if ((int) cuerpo->getVelocidadY() < 0) setJumpAnimation();

    else {
        if (isDucking && isGrounded() == true) setDuckAnimation();
        else if (dirMoving != 0) setWalkingAnimation();
        else setStandAnimation();
    }

    playerSprite->setPosition(posx * PPM, posy * PPM);
    playAnimation();

    if (weapon != NULL) weapon->update(posx, posy+0.2);

    if (!isPlayerDead()) checkMapBounds();

}

void Player::checkMapBounds() {
    float pY = getPositionY() * -1;
    float maxY = Partida::getInstance()->mapa->yTiles * -32 * MPP;

    if (pY < maxY) {
        die(dirLooking);
        Partida::getInstance()->players2Delete.push_back(this);
        //cuerpo->setVelocidad(0,0);
        //eraseBody();
    }
}

SpriteAnimated& Player::getPlayerSprite() {
    return *playerSprite;
}

void Player::jump() {

    if (!isDead) {
        if (canJump) {
            cuerpo->setVelocidadY(0);
            cuerpo->aplicarFuerza(0, fuerzaSalto);
            canJump = false;
            updateCanJumpState = false;
        }
    }

}

//Comprobamos si se puede saltar

bool Player::isGrounded() {
    return ( fabs(cuerpo->getVelocidadY()) <= 0.00000005 ? true : false);
}

bool Player::updateCanJumpStateState() {
    updateCanJumpState = true;
}

void Player::changeDirection(int newDirMov) {
    if (!isDead) {
        dirMoving = newDirMov;

        if (dirMoving != 0) {
            if (dirLooking != dirMoving) {
                cuerpo->setVelocidadX(-cuerpo->getVelocidadX());
                playerSprite->scale(-1, 1);
                dirLooking = dirMoving;

                if (weapon != NULL) {
                    weapon->setDir(dirLooking); //TODO : cambiar la rotacion del arma
                }

            }
        }
    }
}

void Player::move() {
    if (!isDead) {
        if (abs((int) cuerpo->getVelocidadX()) < velocidadMaxima && !isDucking) {
            cuerpo->aplicarFuerza(fuerzaMovimiento * dirMoving, 0);
        }
    }
}

void Player::duck(int new_dir) {
    if (!isDead) {
        if (new_dir == 1) isDucking = true;
        else if (new_dir == 0) isDucking = false;
    }
}

void Player::die(int dir) {
    if (!isDead) {
        changeDirection(-dir);
        cuerpo->aplicarFuerza(fuerzaMovimiento * 5 * dir, -30);
        if (weapon != NULL) {
            weapon->setDir(dir);
            weapon->throwWeapon(dir);
            weapon = NULL;
        }
        isDead = true;
        downgradeMonedero();
        Motorgrafico::getInstance()->getMusicPlayer()->playSFX(Motorgrafico::getInstance()->getMusicPlayer()->death);
    }
}

bool Player::isPlayerDead() {
    return isDead;
}

void Player::mock() {
    float random_level = 0.75 + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (1.25 - 0.75)));
    //std::cout << random_level << endl;
    Motorgrafico::getInstance()->getMusicPlayer()->setSFXPitchBend(Motorgrafico::getInstance()->getMusicPlayer()->ech220, random_level);
    Motorgrafico::getInstance()->getMusicPlayer()->playSFX(Motorgrafico::getInstance()->getMusicPlayer()->ech220);
}

void Player::shoot() {
    if (!isDead) {
        if (weapon != NULL) {
            int recoil = weapon->shoot();
            if (abs((int) cuerpo->getVelocidadX()) < velocidadMaxima * 4 / 3) {

                if (!isDucking) cuerpo->aplicarFuerza(recoil * dirLooking*-1, 0);
                else cuerpo->aplicarFuerza(recoil * dirLooking * -1, -recoil);
            }

        }
    }
}

void Player::respawn() {
    dirMoving = 0;
    isDucking = false;
    isDead = false;
    cuerpo->setActive(true);
    if (hasWeapon()) {
        weapon->throwWeapon(0);
        weapon = NULL;
    }
}

void Player::interact(Weapon* lastWeapon) {

    if (!isDead) {
        Partida *partida = Partida::getInstance();
        vector<Weapon*> worldWeapons = partida->worldWeapons;
        for (int i = 0; i < worldWeapons.size(); i++) {
            if (worldWeapons.at(i) != NULL) {
                Weapon *currentWeapon = worldWeapons.at(i);
                if (playerSprite->getGlobalBounds().intersects(currentWeapon->m_vBody->getBounds())) {
                    if (!currentWeapon->inPossession && currentWeapon != lastWeapon && currentWeapon->ammo != 0) {
                        currentWeapon->setPossession(true);

                        currentWeapon->cuerpo->setActive(false);
                        currentWeapon->cuerpo->setAwake(false);

                        weapon = currentWeapon;
                        if (dirLooking != weapon->dir) weapon->setDir(dirLooking);
                        break;
                    }
                }
            }
        }

    }
}

void Player::interact() {

    if (!isDead) {
        Partida *partida = Partida::getInstance();
        vector<Weapon*> worldWeapons = partida->worldWeapons;

        if (weapon == NULL) {
            for (int i = 0; i < worldWeapons.size(); i++) {
                if (worldWeapons.at(i) != NULL) {
                    Weapon *currentWeapon = worldWeapons.at(i);
                    if (playerSprite->getGlobalBounds().intersects(currentWeapon->m_vBody->getBounds())) {
                        if (!currentWeapon->inPossession && currentWeapon->ammo != 0) {
                            currentWeapon->setPossession(true);

                            currentWeapon->cuerpo->setActive(false);
                            currentWeapon->cuerpo->setAwake(false);
                            weapon = currentWeapon;

                            if (dirLooking != weapon->dir)weapon->setDir(dirLooking);

                            break;
                        }
                    }
                }
            }
        } else {
            weapon->throwWeapon(cuerpo->getVelocidadX());
            Weapon* lastWeapon = weapon;
            weapon = NULL;
            interact(lastWeapon);
        }
    }

}

void Player::pause() {
    paused = !paused;
}

bool Player::getPaused() {
    return paused;
}

float Player::getPositionX() {
    return (cuerpo->getPosicionX());
}

float Player::getPositionY() {
    return (cuerpo->getPosicionY());
}

void Player::setPosition(float posX, float posY) {
    cuerpo->setPosicion(posX*MPP, posY * MPP);
}

int Player::getDirMoving() {
    return dirMoving;
}

void Player::setColor(int id) {
    Color *color = new Color(0, 0, 0);
    switch (id) {
        case 0:
            color->r = 255;
            color->g = 255;
            color->b = 255;
            break;
        case 1:
            color->r = 255;
            color->g = 070;
            color->b = 070;
            break;
        case 2:
            color->r = 070;
            color->g = 255;
            color->b = 070;
            break;
        case 3:
            color->r = 070;
            color->g = 070;
            color->b = 255;
            break;
    }
    playerSprite->setColor(*color);
}

bool Player::hasWeapon() {
    if (this->weapon == NULL) return (false);
    else return (true);
}

Weapon* Player::getWeapon() {
    return (this->weapon);
}

bool Player::isJumping() {
    return !canJump;
}

void Player::Contact(void* punt, string tipo) {
    if (tipo.compare("Platform") != 0) {
        Partida* partida = Partida::getInstance();
        int dir = -1;

        if (tipo.compare("Bala") == 0) {
            Bala* bala = static_cast<Bala*> (punt);
            if (bala->cuerpo->getPosicionX() < this->getPositionX()) {
                dir = 1;
            }
            this->changeDirection(dir);
            partida->players2Delete.push_back(this);
        } else if (tipo.compare("Explosion") == 0) {
            Explosion* explo = static_cast<Explosion*> (punt);
            if (explo->cuerpo->getPosicionX() < this->getPositionX()) {
                dir = 1;
            }
            this->changeDirection(dir);
            partida->players2Delete.push_back(this);
        } else if (tipo.compare("Trampa") == 0) {
            Trampa* trampa = static_cast<Trampa*> (punt);
            int id = trampa->getID();

            switch (id) {
                case 3:
                    break;
                case 4:
                    break;
                default:
                    Trampa* trampa = static_cast<Trampa*> (punt);
                    if (trampa->getCuerpo()->getPosicionX() < this->getPositionX()) {
                        dir = 1;
                    }
                    this->changeDirection(dir);
                    partida->players2Delete.push_back(this);
                    break;
            }

        }

    }
}

void Player::Contact(void* punt, string tipo, int id) {
    if (tipo.compare("Platform") != 0) {
        Partida* partida = Partida::getInstance();
        int dir = -1;

        if (tipo.compare("Trampa") == 0) {

            switch (id) {
                case 3:
                    break;
                case 4:
                    break;
                default:
                    Trampa* trampa = static_cast<Trampa*> (punt);
                    if (trampa->getCuerpo()->getPosicionX() < this->getPositionX()) {
                        dir = 1;
                    }
                    this->changeDirection(dir);
                    partida->players2Delete.push_back(this);
                    break;
            }

        }

    }
}

void Player::give1Point() {
    points++;
}

int Player::getPoints() {
    return points;
}

string Player::getTexture() {
    return Resources::getInstance()->sprites;
}

void Player::upgradeMonedero(int value) {
    monedero += value;
}

void Player::downgradeMonedero() {
    if (monedero * 0.7 >= 1) decreasedCoins = monedero - (int) monedero * 0.7 + 1;
    else decreasedCoins = 0;
    monedero = monedero * 0.7;
}

void Player::resetMonedero() {
    monedero = 0;
}

int Player::getMonedero() {
    return monedero;
}

int Player::getDecreasedCoins() {
    return decreasedCoins;
}

int Player::collidesWithCoin() {
    int value = -1;
    if (!isDead) {
        Partida *partida = Partida::getInstance();
        vector<Coin*> worldCoins = partida->worldCoins;
        for (int i = 0; i < worldCoins.size(); i++) {
            if (worldCoins.at(i) != NULL) {
                if (playerSprite->getGlobalBounds().intersects(worldCoins.at(i)->getVisibleBody().getBounds())) {
                    if (!worldCoins.at(i)->getInPossession()) {
                        worldCoins.at(i)->setPossession(true);
                        upgradeMonedero(worldCoins.at(i)->getValue());
                        Motorgrafico::getInstance()->getMusicPlayer()->playSFX(Motorgrafico::getInstance()->getMusicPlayer()->coin1);
                        //cout<<"Mi monedero actual: "<<ceil(monedero)<<endl;
                        value = worldCoins.at(i)->getValue();
                    }
                }
            }
        }
    }
    return value;
}

InnerClock* Player::getCoinsClock() {
    return coinsClock;
}

InnerClock* Player::getRespawnClock() {
    return respawnClock;
}

float Player::getCoinsTime() {
    return coinsTime;
}

float Player::getRespawnTime() {
    return respawnTime;
}

void Player::addCoinDeltaTime() {
    coinsTime += coinsClock->getDeltaTimeAsSeconds();

}

void Player::addRespawnDeltaTime() {
    respawnTime += coinsClock->getDeltaTimeAsSeconds();

}

void Player::resetCoinsTime() {
    coinsTime = 0;
}

void Player::resetRespawnTime() {
    respawnTime = 0;
}