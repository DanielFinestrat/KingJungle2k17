#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include "Box2D/Box2D.h"
#include "Animation.h"
#include "SpriteAnimated.h"

#define TIMESTEP 1.0f/15.f      //TIEMPO DE REFRESCO
#define VELITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA POSICION

#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

#define screenWidth 800
#define screenHeight 600

#define fuerzaSalto -65
#define fuerzaMovimiento 5
#define velocidadMaxima 1

using namespace std;
using namespace sf;

bool movimiento = false;
bool saltar = false;
bool agachar = false;

bool canJump = true;

//Nuestros Jugadores
struct Caja{
    Vector2f m_Size;
    b2Body *m_pBody;
    
    Caja(){ m_Size = Vector2f(50.0f, 50.0f); }
    Caja(Vector2f size){ m_Size = size; }
};

//Una clase que permitirá saber si se ha soltado un botón
struct JoystickState{
    bool jumpButtonPressed;
    bool dirDcha;
    
    JoystickState(){
        jumpButtonPressed = false;
        dirDcha = true;
    }
};

struct PlayerAnimation{
    Texture texture;
    Animation standAnimation; //animacion de estar quieto
    Animation walkingAnimation; //animacion de andar
    Animation jumpAnimation; // animacion de saltar
    Animation duckAnimation;//animacion de agacharse
    Animation* currentAnimation; //establecemos la animacion por defecto
    SpriteAnimated* playerSprite;
    
    PlayerAnimation(){
        //cargamos la textura
        if (!texture.loadFromFile("resources/sprites.png")){
            cout << "Failed to load player spritesheet!" << std::endl;
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
       jumpAnimation.addFrame(IntRect(149,275-70,196-149,70));
       jumpAnimation.addFrame(IntRect(199,275-70,247-199,70));
       jumpAnimation.addFrame(IntRect(250,275-70,303-250,70));
       jumpAnimation.addFrame(IntRect(306,285-70,351-306,70));
       jumpAnimation.addFrame(IntRect(354,285-70,399-354,70));

       standAnimation.setSpriteSheet(texture);
       standAnimation.addFrame(IntRect(4 , 0 , 38-4, 67));
       standAnimation.addFrame(IntRect(41 , 0 , 74-41, 67));
       standAnimation.addFrame(IntRect(77 , 0 ,110-77, 67));
       
       duckAnimation.setSpriteSheet(texture);
       duckAnimation.addFrame(IntRect(3,298-70,51-3,70));       
       
       currentAnimation = &standAnimation; //establecemos la animacion por defecto
       playerSprite = new SpriteAnimated(seconds(0.2), true, false);// Creamos un sprite animado
    }
};

void Update_Shape(Caja caixa, SpriteAnimated &playerSprite){
    b2Vec2 pos = caixa.m_pBody->GetPosition();
    playerSprite.setPosition(pos.x * PPM, pos.y * PPM);
}

void crearJugador(b2World *world, vector<Caja> *m_vCajas, vector<JoystickState> *joystickStateVector){
    int randSize = 50 + rand()%(100+1 -50);
    Vector2f pos = Vector2f(screenWidth/2, screenHeight/2);
    Caja nuevaCaja = Caja(Vector2f(randSize, randSize));

    b2PolygonShape polyShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    //Definimos un cuerpo dinamico (afectando por la gravedad y resto de objetos box2d creados)
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x * MPP, pos.y * MPP);
    bodyDef.gravityScale = 0.7;
    bodyDef.fixedRotation = true;
    nuevaCaja.m_pBody = world->CreateBody(&bodyDef);
    polyShape.SetAsBox(randSize/2 * MPP, randSize/2 * MPP);

    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.05;
    fixtureDef.density = 0.7f;

    nuevaCaja.m_pBody->CreateFixture(&fixtureDef);

    m_vCajas->push_back(nuevaCaja);
    JoystickState joystickState;
    joystickStateVector->push_back(joystickState);
}

void movePlayer(Joystick *joysticks, vector<JoystickState> *joystickStateVector, bool isPlayerPresent[4], vector<Caja> *m_vCajas, SpriteAnimated &playerSprite){
    for(int i = 0; i < 4; i++){
        if(isPlayerPresent[i]){
            
            //SALTO
            //Comprobamos si puede saltar
            if(!canJump && fabs(m_vCajas->at(i).m_pBody->GetLinearVelocity().y) <= 0.005){
                canJump = true;
                saltar = false;
            }
            //Si podemos saltar y el botón no estaba presionado, saltamos
            if(canJump && !joystickStateVector->at(i).jumpButtonPressed && joysticks->isButtonPressed(i, 2)){
                joystickStateVector->at(i).jumpButtonPressed = true;
                m_vCajas->at(i).m_pBody->SetLinearVelocity(b2Vec2(m_vCajas->at(i).m_pBody->GetLinearVelocity().x,0));
                m_vCajas->at(i).m_pBody->ApplyForceToCenter(b2Vec2(0, fuerzaSalto), 1);
                saltar = true;
                canJump = false;
            }
            //Si el botón ha dejado de ser presionado, lo actualizamos
            else if(joystickStateVector->at(i).jumpButtonPressed && !joysticks->isButtonPressed(i, 2)){
                joystickStateVector->at(i).jumpButtonPressed = false;
            }
            
            //MOVERSE IZDA/DCHA
            if(joysticks->getAxisPosition(i, joysticks->X) > 10 || joysticks->getAxisPosition(i, joysticks->X) < -10 ){
                
                bool nuevaDirDerecha = joysticks->getAxisPosition(i,joysticks->X) > 0 ? true : false;
                if(joystickStateVector->at(i).dirDcha != nuevaDirDerecha){
                    playerSprite.scale(-1,1);
                    joystickStateVector->at(i).dirDcha = nuevaDirDerecha;
                }
                
                int dir = nuevaDirDerecha ? 1 : -1;
                if(abs((int)m_vCajas->at(i).m_pBody->GetLinearVelocity().x) < velocidadMaxima){
                    m_vCajas->at(i).m_pBody->ApplyForceToCenter(b2Vec2(fuerzaMovimiento*dir, 0),true);
                }
                movimiento = true;    
            }
            
            //Parar de moverse eje x
            if(joysticks->getAxisPosition(i, joysticks->X) < 10 && joysticks->getAxisPosition(i, joysticks->X) > -10 ){
                if (movimiento){
                    int dir = joystickStateVector->at(i).dirDcha ? -1 : 1;
                    m_vCajas->at(i).m_pBody->ApplyForceToCenter(b2Vec2(fuerzaMovimiento*dir*0.75, 0), true);
                    movimiento = false;
                }
            }
            
            
            //AGACHARSE
            if(joysticks->getAxisPosition(i, joysticks->Y) >= 10 ){ agachar = true; }
            if(joysticks->getAxisPosition(i, joysticks->Y) < 10 ){ agachar = false; }
        }
    }
}

int main() {
    //Vector con las cajas a dibujar
    vector<Caja> m_vCajas;
    
    //Definir Mundo Box2D (El parametro es la gravedad)
    b2World world(b2Vec2(0.0f, 9.8f));
    
    //Crear Ventana
    RenderWindow Ventana(VideoMode(screenWidth, screenHeight),"Ejemplo JoyStick + Sprites");
    //Hacer que los tiempos de refresco casen con los tiempos de Box2D
    Ventana.setFramerateLimit(60);
    
    //Definir Suelo Box2D y SFML
    b2BodyDef sueloBodyDef;
    sueloBodyDef.position.Set(screenWidth/2*MPP, 550.0f*MPP);
    b2Body* sueloBody = world.CreateBody(&sueloBodyDef);
    b2PolygonShape sueloBox;
    sueloBox.SetAsBox(800.0f/2*MPP, 100.0f/2*MPP);
    sueloBody->CreateFixture(&sueloBox, 0.0f);
    
    RectangleShape rectSuelo(Vector2f(screenWidth, 100));
    rectSuelo.setOrigin(screenWidth/2, 100/2);
    rectSuelo.setPosition(Vector2f(sueloBody->GetPosition().x*PPM, sueloBody->GetPosition().y * PPM));
    rectSuelo.setFillColor(Color::Blue);
    
    //Definir Techo Box2D y SFML
    b2BodyDef techoBodyDef;
    techoBodyDef.position.Set(screenWidth/4*MPP, 350.0f*MPP);
    b2Body* techoBody = world.CreateBody(&techoBodyDef);
    b2PolygonShape techoBox;
    techoBox.SetAsBox(800.0f/2*MPP, 100.0f/2*MPP);
    techoBody->CreateFixture(&sueloBox, 0.0f);
    
    RectangleShape rectTecho(Vector2f(screenWidth, 100));
    rectTecho.setOrigin(screenWidth/2, 100/2);
    rectTecho.setPosition(Vector2f(techoBody->GetPosition().x*PPM, techoBody->GetPosition().y * PPM));
    rectTecho.setFillColor(Color::Red);
    
    //Creamos un objeto controlador de joysticks,
    //un objeto de estado de botones y un vector de presencia de jugadores
    Joystick joysticks;
    vector<JoystickState> joystickStateVector;
    bool isPlayerPresent[4] = {false, false, false, false};
        
    PlayerAnimation playerAnimation;
    SpriteAnimated playerSprite(seconds(0.1),true,false);
    playerSprite.setOrigin(50/2, 50/2);

    //reloj con el que cambiaran los frames de la aminacion
    Clock frameClock;
    
    while(Ventana.isOpen()){
        
        Time frameTime = frameClock.restart();//reseteamos el tiempo de los frames
    
        //Control de conexión de personajes
        for(int i = 0; i < 4; i++){
            if(isPlayerPresent[i] == false && joysticks.isConnected(i)){
                isPlayerPresent[i] = true;
                crearJugador(&world, &m_vCajas, &joystickStateVector);
            }
        }
        
        //Control de movimiento de personajes
        movePlayer(&joysticks, &joystickStateVector, isPlayerPresent, &m_vCajas, playerSprite);
        
        Event event;
        while (Ventana.pollEvent(event)) {
            switch (event.type) {
            case Event::Closed:
                Ventana.close();
                break;
            }
        }

        //Actualiza mundo Box2D
        world.Step(TIMESTEP, VELITER, POSITER);

        //Limpiamos ventana
        Ventana.clear(Color::Black);  
        
        //Actualizamos la caja
        for(vector<Caja>::iterator it=m_vCajas.begin(); it != m_vCajas.end(); ++it){    
            Update_Shape(*it, playerSprite);
        }

        //playerAnimation.currentAnimation = movimiento ? &playerAnimation.walkingAnimation : &playerAnimation.standAnimation;
        //playerAnimation.currentAnimation = saltar ? &playerAnimation.jumpAnimation : &playerAnimation.standAnimation;
        if(movimiento)playerAnimation.currentAnimation = &playerAnimation.walkingAnimation;
        else if(saltar) playerAnimation.currentAnimation =&playerAnimation.jumpAnimation;
        else if(agachar) playerAnimation.currentAnimation =&playerAnimation.duckAnimation;
        else playerAnimation.currentAnimation =&playerAnimation.standAnimation;
        
        
        //pone en movimiento la animacion actual
        playerSprite.play(*playerAnimation.currentAnimation);
        
        //actualizar el sprite del jugador
        playerSprite.update(frameTime);
        
        //Dibujamos el suelo
        Ventana.draw(rectSuelo);
        Ventana.draw(rectTecho);
        
        //Dinujamos sprite
        Ventana.draw(playerSprite);
        
        //Lo mostramos todo
        Ventana.display();
    }
        

    return 0;
}
