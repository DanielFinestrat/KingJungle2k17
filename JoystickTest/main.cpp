#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include "Box2D/Box2D.h"

#define TIMESTEP 1.0f/60.f      //TIEMPO DE REFRESCO
#define VELITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA POSICION

#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

#define screenWidth 800
#define screenHeight 600

using namespace std;
using namespace sf;

//Nuestros Jugadores
struct Caja{
    Vector2f m_Size;
    b2Body *m_pBody;
    RectangleShape m_Shape;
    
    Caja(){ m_Size = Vector2f(50.0f, 50.0f); }
    Caja(Vector2f size){ m_Size = size; }
};

//Una clase que permitirá saber si se ha soltado un botón
struct JoystickState{
    bool jumpButtonPressed;
    
    JoystickState(){ jumpButtonPressed = false; }
};

RectangleShape Update_Shape(Caja caixa){
    RectangleShape rectCaja(caixa.m_Size);
    rectCaja.setOrigin(caixa.m_Size.x/2, caixa.m_Size.y/2);
    rectCaja.setFillColor(Color::Red);

    float angle = caixa.m_pBody->GetAngle();
    b2Vec2 pos = caixa.m_pBody->GetPosition();

    rectCaja.setPosition(pos.x * PPM, pos.y * PPM);
    rectCaja.setRotation((angle*180)/M_PI);
    return rectCaja;
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
    nuevaCaja.m_pBody = world->CreateBody(&bodyDef);
    polyShape.SetAsBox(randSize/2 * MPP, randSize/2 * MPP);

    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.3f;
    fixtureDef.density = 0.7f;

    nuevaCaja.m_pBody->CreateFixture(&fixtureDef);

    m_vCajas->push_back(nuevaCaja);
    JoystickState joystickState;
    joystickStateVector->push_back(joystickState);
}

void movePlayer(Joystick *joysticks, vector<JoystickState> *joystickStateVector, bool isPlayerPresent[4], vector<Caja> *m_vCajas){
    for(int i = 0; i < 4; i++){
        if(isPlayerPresent[i]){
            
            //SALTAR
            
            //Si el botón no estaba presionado, saltamos
            if(!joystickStateVector->at(i).jumpButtonPressed && joysticks->isButtonPressed(i, 2)){
                joystickStateVector->at(i).jumpButtonPressed = true;
                m_vCajas->at(i).m_pBody->ApplyForceToCenter(b2Vec2(0, -200), 1);
            }
            //Si el botón ha dejado de ser presionado, lo actualizamos
            else if(joystickStateVector->at(i).jumpButtonPressed && !joysticks->isButtonPressed(i, 2)){
                joystickStateVector->at(i).jumpButtonPressed = false;
            }
            
            //MOVERSE IZDA/DCHA
            if(joysticks->getAxisPosition(i, joysticks->X) != 0 ){
                m_vCajas->at(i).m_pBody->SetLinearVelocity(b2Vec2(0.05 * joysticks->getAxisPosition(i, joysticks->X), m_vCajas->at(i).m_pBody->GetLinearVelocity().y));
            }
            //Parar
            if(joysticks->getAxisPosition(i, joysticks->X) == 0 ){
                m_vCajas->at(i).m_pBody->SetLinearVelocity(b2Vec2(0, m_vCajas->at(i).m_pBody->GetLinearVelocity().y));
            }
            
        }
    }
}

int main() {

    //Vector con las cajas a dibujar
    vector<Caja> m_vCajas;
    
    //Definir Mundo Box2D (El parametro es la gravedad)
    b2World world(b2Vec2(0.0f, 9.8f));
    
    //Definir Suelo Box2D
    b2BodyDef sueloBodyDef;
    sueloBodyDef.position.Set(screenWidth/2*MPP, 550.0f*MPP);
    b2Body* sueloBody = world.CreateBody(&sueloBodyDef);
    b2PolygonShape sueloBox;
    sueloBox.SetAsBox(800.0f/2*MPP, 100.0f/2*MPP);
    sueloBody->CreateFixture(&sueloBox, 0.0f);
    
    //Crear Ventana
    RenderWindow Ventana(VideoMode(screenWidth, screenHeight),"Ejemplo JoyStick");
    //Hacer que los tiempos de refresco casen con los tiempos de Box2D
    Ventana.setFramerateLimit(60);
    
    //Creamos un rectangulo que actuara de suelo más adelante
    RectangleShape rectSuelo(Vector2f(screenWidth, 100));
    rectSuelo.setOrigin(screenWidth/2, 100/2);
    rectSuelo.setPosition(Vector2f(sueloBody->GetPosition().x*PPM, sueloBody->GetPosition().y * PPM));
    rectSuelo.setFillColor(Color::Blue);
    
    //Creamos un objeto controlador de joysticks,
    //un objeto de estado de botones y un vector de presencia de jugadores
    Joystick joysticks;
    vector<JoystickState> joystickStateVector;
    bool isPlayerPresent[4] = {false, false, false, false};
    
    while(Ventana.isOpen()){
    
        //Control de conexión de personajes
        for(int i = 0; i < 4; i++){
            if(isPlayerPresent[i] == false && joysticks.isConnected(i)){
                isPlayerPresent[i] = true;
                crearJugador(&world, &m_vCajas, &joystickStateVector);
            }
        }
        
        //Control de movimiento de personajes
        movePlayer(&joysticks, &joystickStateVector, isPlayerPresent, &m_vCajas);
        
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
        
        //Dibujamos las cajas creadas por el usuario
        for(vector<Caja>::iterator it=m_vCajas.begin(); it != m_vCajas.end(); ++it){    
            Ventana.draw(Update_Shape(*it)); //Dibujamos el elemento en el buffer
        }
        
        //Dibujamos el suelo
        Ventana.draw(rectSuelo);
        //Lo mostramos todo
        Ventana.display();
    }
        

    return 0;
}
