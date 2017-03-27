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

void update(Caja &nuevaCaja, b2BodyDef &bodyDef) {
    
    nuevaCaja.m_pBody->SetTransform(nuevaCaja.m_pBody->GetPosition(),0);
    nuevaCaja.m_Shape.setRotation(nuevaCaja.m_pBody->GetAngle());
    nuevaCaja.m_Shape.setPosition(nuevaCaja.m_pBody->GetPosition().x*PPM, nuevaCaja.m_pBody->GetPosition().y*PPM);
    
}



int main() {

    //Definir Mundo Box2D (El parametro es la gravedad)
    b2World world(b2Vec2(0.0f, 9.8f));
    
    //Definir Suelo Box2D
    b2BodyDef sueloBodyDef;
    sueloBodyDef.position.Set(400.f*MPP, 550.0f*MPP);
    b2Body* sueloBody = world.CreateBody(&sueloBodyDef);
    b2PolygonShape sueloBox;
    sueloBox.SetAsBox(400.0f*MPP, 50.0f*MPP);
    sueloBody->CreateFixture(&sueloBox, 0.0f);
    
    //Creamos su respectivo rectangulo en SFML para poder visualizarlo
    RectangleShape rectSuelo(Vector2f(800, 100));
    rectSuelo.setOrigin(800/2, 100/2);
    rectSuelo.setPosition(Vector2f(sueloBody->GetPosition().x*PPM, sueloBody->GetPosition().y * PPM));
    rectSuelo.setFillColor(Color::Green);
    
    //Definir Left Wall Box2D
    b2BodyDef leftWallDef;
    leftWallDef.position.Set(20.0f*MPP,300*MPP); //Asignamos la posicion de la caja
    b2Body* leftWallBody = world.CreateBody(&leftWallDef); //Creamos el cuerpo en el mundo
    b2PolygonShape leftWallBox; //Creamos la caja
    leftWallBox.SetAsBox(10.0f*MPP, 300.0f*MPP); //Le damos un tamaño a la caja
    leftWallBody->CreateFixture(&leftWallBox, 0.0f); //Creamos la fixture de la caja
    
    //Creamos su respectivo rectangulo en SFML para poder visualizarlo
    RectangleShape rectLeftWall(Vector2f(20,600)); //Creamos el rectangulo con un tamaño
    rectLeftWall.setOrigin(20/2, 600/2); //Definimos su punto central
    rectLeftWall.setPosition(Vector2f(leftWallBody->GetPosition().x*PPM, leftWallBody->GetPosition().y*PPM)); //La posicionamos en en el lugar del cuerpo creado anteriormente
    rectLeftWall.setFillColor(Color::Cyan); //Le asignamos un color
    
    
    //Definir Left Wall Box2D
    b2BodyDef bodyDefDef;
    bodyDefDef.position.Set(780.0f*MPP,300*MPP); //Asignamos la posicion de la caja
    b2Body* bodyDefBody = world.CreateBody(&bodyDefDef); //Creamos el cuerpo en el mundo
    b2PolygonShape bodyDefBox; //Creamos la caja
    bodyDefBox.SetAsBox(10.0f*MPP, 300.0f*MPP); //Le damos un tamaño a la caja
    bodyDefBody->CreateFixture(&bodyDefBox, 0.0f); //Creamos la fixture de la caja
    
    //Creamos su respectivo rectangulo en SFML para poder visualizarlo
    RectangleShape rectRightWall(Vector2f(20,600)); //Creamos el rectangulo con un tamaño
    rectRightWall.setOrigin(20/2, 600/2); //Definimos su punto central
    rectRightWall.setPosition(Vector2f(bodyDefBody->GetPosition().x*PPM, bodyDefBody->GetPosition().y*PPM)); //La posicionamos en en el lugar del cuerpo creado anteriormente
    rectRightWall.setFillColor(Color::Cyan); //Le asignamos un color
    
    
    //Vector de posiciones para los lugares de aparicion de las armas, deben estar en en metros (para el box2D)
    float vectorPos[5][2] = {{300.0f/PPM,300.0f/PPM}, {100.0f/PPM, 50.0f/PPM}, {400.0f/PPM, 175.0f/PPM}, {500.0f/PPM, 200.0f/PPM}, {700.0f/PPM, 100.0f/PPM}};
    
    
    //Creamos la caja
    Caja nuevaCaja = Caja(Vector2f(50,50));

    b2PolygonShape polyShape; //Forma del poligono
    b2FixtureDef fixtureDef; //Fixture
    b2BodyDef bodyDef; //Cuerpo

    bodyDef.type = b2_dynamicBody; //Definimos un cuerpo dinamico (afectando por la gravedad y resto de objetos box2d creados)
    int random = rand() % 5; //Definimos un número random
    bodyDef.position.Set(vectorPos[random][0], vectorPos[random][1]); //Asignamos la posicion aleatoria
    nuevaCaja.m_pBody = world.CreateBody(&bodyDef); //Creamos el cuerpo en el mundo
    polyShape.SetAsBox(25.0f * MPP, 25.0F * MPP); //Le damos un tamaño (se calcula desde el centro)

    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.3f;
    fixtureDef.density = 0.7f;
    nuevaCaja.m_pBody->CreateFixture(&fixtureDef); //Creamos la fixture
    
    //Creamos su respectivo rectangulo en SFML para poder visualizarlo
    nuevaCaja.m_Shape.setSize(Vector2f(50,50)); //Creamos el rectangulo con un tamaño
    nuevaCaja.m_Shape.setOrigin(25, 25); //Definimos su punto central
    nuevaCaja.m_Shape.setPosition(Vector2f(nuevaCaja.m_pBody->GetPosition().x*PPM, nuevaCaja.m_pBody->GetPosition().y*PPM)); //La posicionamos en en el lugar del cuerpo creado anteriormente
    nuevaCaja.m_Shape.setFillColor(Color::White); //Le asignamos un color
        
    //Carga de la textura
    Texture textura;
    
    if (!textura.loadFromFile("./resources/images/revolver.png"))
    {
        std::cerr << "Error cargando la imagen revolver.png" << std::endl;;
        exit(0);
    }
    textura.setSmooth(true);
    nuevaCaja.m_Shape.setTexture(&textura);
    
    
    //Crear Ventana
    RenderWindow Ventana(VideoMode(800,600),"Weapon spawn");
    //Hacer que los tiempos de refresco casen con los tiempos de Box2D
    Ventana.setFramerateLimit(60);
    
    
    while(Ventana.isOpen()){
       
        Event event;
        while (Ventana.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    Ventana.close();
                    break;
                
                case Event::KeyPressed:
                    if (Keyboard::isKeyPressed(Keyboard::Space)) { //Resetea la posicion de la caja.
                        Ventana.clear();
                        
                        
                        nuevaCaja.m_pBody->DestroyFixture(nuevaCaja.m_pBody->GetFixtureList()); //Destruimos la fixture
                        world.DestroyBody(nuevaCaja.m_pBody); //Destruimos el cuerpo del mundo
                        
                        nuevaCaja.m_pBody = world.CreateBody(&bodyDef); //Creamos el cuerpo en el mundo
                        fixtureDef.shape = &polyShape;
                        fixtureDef.friction = 0.2f;
                        fixtureDef.restitution = 0.3f;
                        fixtureDef.density = 0.7f;
                        nuevaCaja.m_pBody->CreateFixture(&fixtureDef); //Creamos la fixture

                        int random = rand() % 5; //Definimos un número random
                        bodyDef.position.Set(vectorPos[random][0], vectorPos[random][1]); //Asignamos la posicion aleatoria
                        
  
                    }

                    break;    
            }

        }
        
        Ventana.clear(Color::Black);

        //Actualiza mundo Box2D
        world.Step(TIMESTEP, VELITER, POSITER);
        
        update(nuevaCaja, bodyDef);

        //Dibujamos los elementos
        Ventana.draw(nuevaCaja.m_Shape);
        Ventana.draw(rectSuelo);
        Ventana.draw(rectLeftWall);
        Ventana.draw(rectRightWall);

        //Lo mostramos todo
        Ventana.display();

    }
}
