/* 
 * File:   Player.h
 * Author: amygwyllion
 *
 * Created on 21 de marzo de 2017, 8:00
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Box2D/Box2D.h"
#include "Entidad.h"
#include "Animation.h"
#include "SpriteAnimated.h"
#include "Weapon.h"

using namespace sf;
using namespace std;

class Player : public Entidad {
public:

    Player();
    Player(b2World&);
    Player(const Player& orig);
    virtual ~Player();
    void setStandAnimation();
    void setWalkingAnimation();
    void setJumpAnimation();
    void setFallAnimation();
    void setDuckAnimation();
    void setDeadAnimation();
    void playAnimation();
    Animation* getCurrentAnimation();
    void update(Time);
    SpriteAnimated& getPlayerSprite();
    void jump();
    bool isGrounded();
    bool updateCanJumpStateState();
    void changeDirection(int);
    void move();
    void duck(int);
    void die();
    bool isPlayerDead();
    void mock(); //TODO
    void shoot();
    void interact();
    void pause(bool); //TODO
    void setPosition(float, float);

private:
    b2Body *m_pBody;
    b2PolygonShape polyShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    Texture texture;
    Animation standAnimation; //Animacion de estar quieto
    Animation walkingAnimation; //Animacion de andar
    Animation jumpAnimation; //Animacion de saltar
    Animation fallAnimation; //Animacion de caer
    Animation duckAnimation; //Animacion de agacharse
    Animation deadAnimation; //Animacion de muerte
    Animation* currentAnimation; //Animacion actual
    SpriteAnimated* playerSprite; //Sprite del jugador

    Weapon *weapon;

    int dirMoving;
    int dirLooking;

    bool updateCanJumpState;
    bool canJump;

    bool isDucking;
    bool isDead;

    float fuerzaSalto;
    float fuerzaMovimiento;
    float velocidadMaxima;
};

#endif /* PLAYER_H */

