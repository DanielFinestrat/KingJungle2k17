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
#include "Box2D/Box2D.h"
#include "Animation.h"
#include "SpriteAnimated.h"

using namespace sf;
using namespace std;

class Player {
    
    public:
        Player();
        Player(b2World&);
        Player(const Player& orig);
        virtual ~Player();
        void setStandAnimation();
        void setWalkingAnimation();
        void setJumpAnimation();
        void setDuckAnimation();
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
        void die(); //TODO
        void mock(); //TODO
        void shoot(); //TODO
        void interact(); //TODO
        void pause(bool); //TODO
        void setPosition(float, float);

    private:
        b2Body *m_pBody;
        b2PolygonShape polyShape;
        b2FixtureDef fixtureDef;
        b2BodyDef bodyDef;
        
        Texture texture;
        Animation standAnimation;       //Animacion de estar quieto
        Animation walkingAnimation;     //Animacion de andar
        Animation jumpAnimation;        //Animacion de saltar
        Animation duckAnimation;        //Animacion de agacharse
        Animation* currentAnimation;    //Animacion actual
        SpriteAnimated* playerSprite;   //Aprite del jugador
        
        int dirMoving;
        int dirLooking;
        
        bool updateCanJumpState;
        bool canJump;
        
        bool isDucking;
        
        float fuerzaSalto;
        float fuerzaMovimiento;
        float velocidadMaxima;
};

#endif /* PLAYER_H */

