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

using namespace std;
using namespace sf;

struct Caja{
    Caja(){ m_Size = Vector2f(50.0f, 50.0f); }
    Caja(Vector2f size){ m_Size = size; }
    
    Vector2f m_Size;
    b2Body *m_pBody;
    RectangleShape m_Shape;
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

int main() {

    //Vector con las cajas a dibujar
    vector<Caja> m_vCajas;
    
    //Definir Mundo Box2D (El parametro es la gravedad)
    b2World world(b2Vec2(0.0f, 9.8f));
    
    //Definir Suelo Box2D
    b2BodyDef sueloBodyDef;
    sueloBodyDef.position.Set(400.f*MPP, 550.0f*MPP);
    b2Body* sueloBody = world.CreateBody(&sueloBodyDef);
    b2PolygonShape sueloBox;
    sueloBox.SetAsBox(800.0f/2*MPP, 100.0f/2*MPP);
    sueloBody->CreateFixture(&sueloBox, 0.0f);
    
    //Crear Ventana
    RenderWindow Ventana(VideoMode(800,600),"Ejemplo Click Box2D");
    //Hacer que los tiempos de refresco casen con los tiempos de Box2D
    Ventana.setFramerateLimit(60);
    
    //Creamos un rectangulo que actuara de suelo más adelante
    RectangleShape rectSuelo(Vector2f(800, 100));
    rectSuelo.setOrigin(800/2, 100/2);
    rectSuelo.setPosition(Vector2f(sueloBody->GetPosition().x*PPM, sueloBody->GetPosition().y * PPM));
    rectSuelo.setFillColor(Color::Blue);
    
    while(Ventana.isOpen()){
       
        Event event;
        while (Ventana.pollEvent(event)) {
            switch (event.type) {
            case Event::Closed:
                Ventana.close();
                break;
                
            case Event::MouseButtonPressed:
                if (event.mouseButton.button == Mouse::Left) {
                    int randSize = 50 + rand()%(100+1 -50);
                    Vector2f posRaton = Vector2f(event.mouseButton.x, event.mouseButton.y);
                    Caja nuevaCaja = Caja(Vector2f(randSize, randSize));
                    
                    b2PolygonShape polyShape;
                    b2FixtureDef fixtureDef;
                    b2BodyDef bodyDef;
                    
                    bodyDef.type = b2_dynamicBody;  //Definimos un cuerpo dinamico (afectando por la gravedad y resto de objetos box2d creados)
                    bodyDef.position.Set(posRaton.x * MPP, posRaton.y * MPP);
                    nuevaCaja.m_pBody = world.CreateBody(&bodyDef);
                    polyShape.SetAsBox(randSize/2 * MPP, randSize/2 * MPP);
                    
                    fixtureDef.shape = &polyShape;
                    fixtureDef.friction = 0.2f;
                    fixtureDef.restitution = 0.3f;
                    fixtureDef.density = 0.7f;
                    
                    nuevaCaja.m_pBody->CreateFixture(&fixtureDef);
                    
                    m_vCajas.push_back(nuevaCaja);
                }
                break;
                
                /*case Event::KeyPressed:
                    for(vector<Caja>::iterator it=m_vCajas.begin(); it != m_vCajas.end(); ++it){
                        (*it).m_pBody->ApplyForce(b2Vec2(0, -200), (*it).m_pBody->GetWorldCenter(), 1);
                    }
                    int cont = 0;
                    for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()){
                        cont++;
                    }
                    cout<<cont<<endl;
                break;*/
            }
        }

        Ventana.clear(Color::Black);
        
        //Actualiza mundo Box2D
        world.Step(TIMESTEP, VELITER, POSITER);
        
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
