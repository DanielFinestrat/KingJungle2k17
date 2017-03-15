#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <set>
#include <vector>
#include "Box2D/Box2D.h"

#define WIDTH 800
#define HEIGHT 600
#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

short CATEGORY_BALA = 0x0001;
short CATEGORY_SCENERY = 0x0002;

short MASK_BALA = CATEGORY_SCENERY;
short MASK_SCENERY = -1;

using namespace std;
using namespace sf;


struct Suelo{
    
    Suelo(b2World *mundo){
        
        b2BodyDef sueloBodyDef;
        sueloBodyDef.position.Set(WIDTH/2 *MPP, (HEIGHT)*MPP);
        m_pBody = mundo->CreateBody(&sueloBodyDef);		
		
        b2PolygonShape sueloBox;
        sueloBox.SetAsBox(WIDTH/2*MPP, 100.0f/2*MPP);
		
		b2FixtureDef sueloFixtureDef;
		sueloFixtureDef.shape = &sueloBox;
		sueloFixtureDef.friction = 0.2f;
		sueloFixtureDef.restitution = 0.3f;
		sueloFixtureDef.density = 0.7f;
		sueloFixtureDef.filter.categoryBits = CATEGORY_SCENERY;
		sueloFixtureDef.filter.maskBits = MASK_SCENERY;
		
        m_pBody->CreateFixture(&sueloFixtureDef);

        m_Shape = sf::RectangleShape(sf::Vector2f(WIDTH, 100));
        m_Shape.setOrigin(WIDTH/2, 100/2);
        m_Shape.setPosition(sf::Vector2f(m_pBody->GetPosition().x*PPM, m_pBody->GetPosition().y*PPM));
        m_Shape.setFillColor(Color::Blue);
    }
    
    b2Body *m_pBody;
    sf::RectangleShape m_Shape;
};

class Bala{
    public:
        sf::Vector2f m_Size;
        b2Body *m_pBody;
        sf::RectangleShape *m_Shape;
        /**
         * Constructor del objeto Bala
         * @param mundo b2World*: mundo en el que estan todos los objetos
         * @param size Vector2f: tamaño de la bala
         */
        Bala(b2World *mundo, sf::Vector2f size, sf::Vector2f position);
        
		/**
         * Actualiza el RectangleShape del objeto
         */
        void Update_Shape();
		
        /** 
         * Le añade una fuerza a la bala en la direccion selecciona afectandole la gravedad
         * @param fuerza float: fuerza a la que se dispara
         * @param angulo float: direccion del movimiento (grados)
         */
        void Disparar_Parabola(float fuerza, float angulo);
        
        /**
         * Le aplica una velocidad constane a la bala en la direccion seleccionada
         * @param velocidad float: velocidad de la bala
         * @param angulo float: direccion del movimiento (grados)
         */
        void Disparar(float velocidad, float angulo);
        
		sf::RectangleShape getShape();
		
        void Delete();
        
        ~Bala();
        
};

class MyContactListener : public b2ContactListener{
    public:
        void BeginContact(b2Contact* contact); 

        void EndContact(b2Contact* contact);
};

set<Bala*> listaDeBalasPorEliminar;

int main(){
	
	set<Bala*> listadoBala;
	
    //Definir Mundo Box2D
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);
    MyContactListener espiaContacto;
    world.SetContactListener(&espiaContacto);
    
    Suelo terra(&world);
    
    //Crear Ventana
    RenderWindow Ventana(VideoMode(WIDTH, HEIGHT), "Pruebas Proyectiles");
    Ventana.setFramerateLimit(60);
    
    while(Ventana.isOpen()){
    
        Event event;
        while(Ventana.pollEvent(event)){
            switch(event.type){
                case Event::Closed:
                    Ventana.close();
                    break;
                case Event::KeyReleased:
                    
                    switch(event.key.code){
                        case Keyboard::Space:
							/*hola->m_pBody->SetTransform(b2Vec2(2,2), hola->m_pBody->GetAngle());
							hola->m_pBody->SetLinearVelocity(b2Vec2(0,0));
							hola->m_pBody->SetAngularVelocity(0);
							hola->Disparar_Parabola(60.0f, 45.0f);	*/
							Bala* nueva;
							nueva = new Bala(&world, sf::Vector2f(30,30), sf::Vector2f(WIDTH/2, 0));
							nueva->Disparar_Parabola(30, 0);
							listadoBala.insert(nueva);
                        break;
                    }
                break;
            }
        }
        

        
        set<Bala*>::iterator it = listaDeBalasPorEliminar.begin();
		set<Bala*>::iterator end = listaDeBalasPorEliminar.end();
		for(; it!=end; ++it){
			Bala* dyingBala = *it;
			listadoBala.erase(dyingBala);
            delete dyingBala;
			
			//cout << dyingBala;
			//dyingBala->Delete();
		}
		listaDeBalasPorEliminar.clear();
		
        
        //proyectil.Update_Shape();


        Ventana.clear(sf::Color::Black);
       
        world.Step(1.0f/60.0f, 10, 10);
        
        Ventana.draw(terra.m_Shape);
		
        //Ventana.draw(proyectil.m_Shape);
		
		it = listadoBala.begin();
		end = listadoBala.end();
		for(; it!=end; ++it){
			Bala* updateBala = *it;
			updateBala->Update_Shape();
			Ventana.draw(updateBala->getShape());
		}

        Ventana.display();
    }
    return 0;
}


//----------------------------------------------------------------------------------------Bala
Bala::Bala(b2World *mundo, sf::Vector2f size, sf::Vector2f position){

	m_Size = size;

	b2BodyDef balaBodyDef;
	balaBodyDef.userData = this;
	balaBodyDef.type = b2_dynamicBody;
	balaBodyDef.position.Set(position.x*MPP, position.y*MPP);
	m_pBody = mundo->CreateBody(&balaBodyDef);

	b2PolygonShape balaBox;
	balaBox.SetAsBox(size.x/2*MPP, size.y/2*MPP);
            
	b2FixtureDef balaFixtureDef;
	balaFixtureDef.shape = &balaBox;
	balaFixtureDef.friction = 0.2f;
	balaFixtureDef.restitution = 0.3f;
	balaFixtureDef.density = 0.7f;
	balaFixtureDef.filter.categoryBits = CATEGORY_BALA;
	balaFixtureDef.filter.maskBits = MASK_BALA;
            
	m_pBody->CreateFixture(&balaFixtureDef);

	m_Shape =  new sf::RectangleShape(size);
    m_Shape->setOrigin(size.x/2, size.y/2);
    m_Shape->setPosition(sf::Vector2f(m_pBody->GetPosition().x*PPM, m_pBody->GetPosition().y*PPM));
    m_Shape->setFillColor(Color::White);
}
    
void Bala::Update_Shape(){
            
	float angle = m_pBody->GetAngle();
    b2Vec2 pos = m_pBody->GetPosition();
            
	m_Shape->setPosition(pos.x * PPM, pos.y * PPM);
	m_Shape->setRotation((angle*180)/M_PI);
}
        
void Bala::Disparar_Parabola(float fuerza, float angulo){
	m_pBody->ApplyForce(b2Vec2(fuerza * cos(angulo*3.14/180.0f), -fuerza * sin(angulo*3.14/180.0f)),m_pBody->GetWorldCenter(), 1);
}
        
void Bala::Disparar(float velocidad, float angulo){
    m_pBody->SetGravityScale(0);
	m_pBody->SetLinearVelocity(b2Vec2(velocidad * cos(angulo*3.14/180.0f), -velocidad * sin(angulo*3.14/180.0f)));
}

void Bala::Delete(){
	m_pBody->GetWorld()->DestroyBody(m_pBody);
	cout << "Delete crashea" << endl;
}

sf::RectangleShape Bala::getShape(){
	return *m_Shape;
}

Bala::~Bala(){
    m_pBody->GetWorld()->DestroyBody(m_pBody);
	delete m_Shape;
	m_Shape = NULL;
	//Hacer un delete de cada objeto que se ha creado con un New y luego igualarlo a NULL
}

//--------------------------------------------------------------------------------------ContactListener
void MyContactListener::BeginContact(b2Contact* contact){
	cout<<"BOOM colision"<<endl;
            
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();	
	
	if(static_cast<Bala*>(bodyUserDataA) && bodyUserDataB == 0){
		listaDeBalasPorEliminar.insert(static_cast<Bala*>(bodyUserDataA));
	}
    
	
	if(static_cast<Bala*>(bodyUserDataB) && bodyUserDataA == 0){
		listaDeBalasPorEliminar.insert(static_cast<Bala*>(bodyUserDataB));
	} 
}

void MyContactListener::EndContact(b2Contact* contact){}