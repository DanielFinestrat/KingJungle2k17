/* 
 * File:   Player.cpp
 * Author: amygwyllion
 * 
 * Created on 21 de marzo de 2017, 8:00
 */

#include "Player.h"
#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

#define pSize 64                //Collider Box Size

Player::Player(){}

Player::Player(b2World &world){
    
   //Cargamos la textura
   if (!texture.loadFromFile("resources/sprites.png")){
       cout << "Failed to load player spritesheet!" << endl;
   }
   
   //Creamos los diferentes frames que va a tener nuestro sprite animado
   walkingAnimation.setSpriteSheet(texture);
   walkingAnimation.addFrame(IntRect(3 , 142 , 49-3 , 207-149));
   walkingAnimation.addFrame(IntRect(52 , 142 , 97-52 , 207-143));
   walkingAnimation.addFrame(IntRect(151 , 142 , 196-151 , 207-143));
   walkingAnimation.addFrame(IntRect(199 , 142 , 243-199 , 207-143));
   walkingAnimation.addFrame(IntRect(293 , 142 , 339-293 , 207-143));
   walkingAnimation.addFrame(IntRect(149 , 142 , 196-149 , 207-143));

   jumpAnimation.setSpriteSheet(texture);
   jumpAnimation.addFrame(IntRect(53,219,98-53,70));
   jumpAnimation.addFrame(IntRect(101,289-70,146-101,70));
   
   fallAnimation.setSpriteSheet(texture);
   fallAnimation.addFrame(IntRect(306,285-70,351-306,70));
   fallAnimation.addFrame(IntRect(354,285-70,399-354,70));

   standAnimation.setSpriteSheet(texture);
   standAnimation.addFrame(IntRect(4 , 0 , 38-4, 67));
   standAnimation.addFrame(IntRect(41 , 0 , 74-41, 67));
   standAnimation.addFrame(IntRect(77 , 0 ,110-77, 67));

   duckAnimation.setSpriteSheet(texture);
   duckAnimation.addFrame(IntRect(3,298-70,51-3,70));
   
   deadAnimation.setSpriteSheet(texture);
   deadAnimation.addFrame(IntRect(3,1470,77-3,1540-1470)); 

   currentAnimation = &standAnimation; //Establecemos la animacion por defecto
   playerSprite = new SpriteAnimated(seconds(0.1), true, false); //Creamos un sprite animado
   playerSprite->setOrigin(pSize/2, pSize/2);
   
   dirMoving = 0;
   dirLooking = 1;
   
   isDead = false;
   
   canJump = true;
   updateCanJumpState = false;
   fuerzaSalto = -80;
   fuerzaMovimiento = 5;
   velocidadMaxima = 1;
   
    //Definimos un cuerpo dinamico (afectando por la gravedad y resto de objetos box2d creados)
    bodyDef.type = b2_dynamicBody;
    bodyDef.gravityScale = 0.7;
    bodyDef.fixedRotation = true;
    m_pBody = world.CreateBody(&bodyDef);
    polyShape.SetAsBox(pSize/2 * MPP, pSize/2 * MPP);

    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0;
    fixtureDef.density = 0.7f;

    m_pBody->CreateFixture(&fixtureDef);
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

void Player::setStandAnimation(){
    currentAnimation = &standAnimation;
}

void Player::setWalkingAnimation(){
    currentAnimation = &walkingAnimation;
}

void Player::setJumpAnimation(){
    currentAnimation = &jumpAnimation;
}

void Player::setFallAnimation(){
    currentAnimation = &fallAnimation;
}

void Player::setDuckAnimation(){
    currentAnimation = &duckAnimation;
}
void Player::setDeadAnimation(){
    currentAnimation = &deadAnimation;
}

void Player::playAnimation(){
    playerSprite->play(*currentAnimation);
}

Animation* Player::getCurrentAnimation(){
    return currentAnimation;
}

void Player::update(Time frameTime){
    playerSprite->update(frameTime);
    b2Vec2 pos = m_pBody->GetPosition();

    move();

    if(!canJump && updateCanJumpState) canJump = isGrounded();
    if(isDead) setDeadAnimation();
    else if((int)m_pBody->GetLinearVelocity().y > 0) setFallAnimation();
    else if((int)m_pBody->GetLinearVelocity().y < 0) setJumpAnimation();
    else{
        if(isDucking && isGrounded()==true) setDuckAnimation();
        else if(dirMoving != 0 ) setWalkingAnimation();
        else setStandAnimation();
    }

    playerSprite->setPosition(pos.x * PPM, pos.y * PPM);
    playAnimation();
}

SpriteAnimated& Player::getPlayerSprite(){
    return *playerSprite;
}

void Player::jump(){
    //SALTO
    if(!isDead){
        if(canJump){
            m_pBody->SetLinearVelocity(b2Vec2(m_pBody->GetLinearVelocity().x,0));
            m_pBody->ApplyForceToCenter(b2Vec2(0, fuerzaSalto), 1);
            canJump = false;
            updateCanJumpState = false;
        }
    }

}

//Comprobamos si se puede saltar
bool Player::isGrounded(){
    return( fabs(m_pBody->GetLinearVelocity().y) <= 0.0000005 ? true : false );
}

bool Player::updateCanJumpStateState(){
    updateCanJumpState = true;
}

void Player::changeDirection(int newDirMov){
    //MOVERSE IZDA/DCHA
    if(!isDead){
        dirMoving = newDirMov;

        if(dirMoving != 0){
            if(dirLooking != dirMoving){
                m_pBody->SetLinearVelocity(b2Vec2(-m_pBody->GetLinearVelocity().x, m_pBody->GetLinearVelocity().y));
                playerSprite->scale(-1,1);
                dirLooking = dirMoving;
            }
        }
    }
}

void Player::move(){
    if(!isDead){
        if(abs((int)m_pBody->GetLinearVelocity().x) < velocidadMaxima && !isDucking){
            m_pBody->ApplyForceToCenter(b2Vec2(fuerzaMovimiento * dirMoving, 0), true);
        }
    }
}

void Player::duck(int new_dir){
    if(!isDead){
        if(new_dir == 1){
            isDucking = true;
        }

        else if(new_dir == 0){
            isDucking = false;
        }
    }
}

void Player::die(){
    if(!isDead){
        m_pBody->ApplyForceToCenter(b2Vec2(fuerzaMovimiento * 5 * -dirLooking, -30), true);
        isDead = true;
    }
}

bool Player::isPlayerDead(){
    return isDead;
}

void Player::mock(){
    
}

void Player::shoot(){
    
}

void Player::interact(){
    
}

void Player::pause(bool paused){
    
}

void Player::setPosition(float posX, float posY){
    m_pBody->SetTransform(b2Vec2(posX*MPP, posY*MPP),0);
}