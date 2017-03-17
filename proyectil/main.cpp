#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <set>
#include <vector>
#include <typeinfo>			//typeid(variable).name())
#include "Box2D/Box2D.h"

#define WIDTH 800
#define HEIGHT 600
#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

int frameCounter = 0;

short CATEGORY_BALA = 0x0001;
short CATEGORY_SCENERY = 0x0002;

short MASK_BALA = CATEGORY_SCENERY;
short MASK_SCENERY = -1;

using namespace std;
using namespace sf;

class Entidad{
	public:
		string tipo;

		Entidad();

		string getTipo();

};

class Suelo : public Entidad {
    
	public:
		Suelo(b2World *mundo);
    
		void Render(sf::RenderWindow *window);
		
		b2Body *m_pBody;
		sf::RectangleShape* m_Shape;
};

class Explosion : public Entidad{
	public:
		float radioActual;
		float radioMax;
		float incrementoRadio;
		
		b2Body *m_pBody;
		sf::CircleShape *m_Shape;

		/**
		 * Constructor del objeto Explosion
		 * @param mundo b2World: mundo en el que estan todos los objetos
		 * @param position Vector2f: posicion de la explosion
		 * @param radio float: radio maxio al que alcanzará la explosión
		 * @param incremento float: valor con el que aumenta el radio con cada iteración
		 * @param inicial float: radio inicial de la explosión
		 */ 
		Explosion(b2World *mundo, sf::Vector2f position, float radio, float incremento, float inicial);
		
		/**
		 * Actualiza el FixtureBodyDef y CircleShape de la explosión
		 */
		void Update();
		
		/**
		 * Renderiza la explosión en la ventana
		 * @param window RenderWindow: Ventana de la aplicación
		 * */
		void Render(sf::RenderWindow *window);
		
		/**
		 * Elimina de memoria las variables de la explosión 
		 */
		~Explosion();

};

class Bala : public Entidad{
    public:
        sf::Vector2f m_Size;
		bool explosion;
        
		b2Body *m_pBody;
        sf::RectangleShape *m_Shape;
		
        /**
         * Constructor del objeto Bala
         * @param mundo b2World*: mundo en el que estan todos los objetos
         * @param size Vector2f: tamaño de la bala
		 * @param position Vector2f: posicion inicial de la bala
		 * @param explo bool: activar la explosion al eliminar la bala
         */
        Bala(b2World *mundo, sf::Vector2f size, sf::Vector2f position, bool explo);
        
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
        
		/**
		 * Renderiza la bala en la ventana
		 * @param window RenderWindow: Ventana de la aplicación
		 */
		void Render(sf::RenderWindow *window);
		
		/**
		* Elimina de memoria las variables de la bala
		*/
        ~Bala();
        
};

class MyContactListener : public b2ContactListener{
    public:
		/**
		 * Función que se ejecuta al empezar una colisión en el mundo
		 * @param contact b2Contact: Elemento con los cuerpos que intervienen en la colisión
		 */
        void BeginContact(b2Contact* contact); 

		/**
		 * Función que se ejecuta al finalizar una colisión en el mundo
		 * @param contact b2Contact: Elemento con los cuerpos que intervienen en la colisión
		 */
        void EndContact(b2Contact* contact);
};

set<Bala*> listaDeBalasPorEliminar;
set<Explosion*> listaDeExploPorEliminar;

set<Bala*> listadoBala;
set<Explosion*> listadoExplosion;

int main(){
	
	
	
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
		
		frameCounter++;
		
        Event event;
        while(Ventana.pollEvent(event)){
            switch(event.type){
                case Event::Closed:
                    Ventana.close();
                    break;
                case Event::KeyReleased:
                    
                    switch(event.key.code){
                        case Keyboard::Space:
							Bala* nueva;
							nueva = new Bala(&world, sf::Vector2f(30,30), sf::Vector2f(WIDTH/2, 0), frameCounter%2);
							listadoBala.insert(nueva);
                        break;
                    }
                break;
            }
        }
        

        //Eliminacion de las balas
        set<Bala*>::iterator itBala = listaDeBalasPorEliminar.begin();
		set<Bala*>::iterator endBala = listaDeBalasPorEliminar.end();
		for(; itBala!=endBala; ++itBala){
			Bala* dyingBala = *itBala;
			if(dyingBala->explosion == true){
				b2Vec2 position = dyingBala->m_pBody->GetPosition();
				
				Explosion *nueva;
				nueva = new Explosion(dyingBala->m_pBody->GetWorld(), sf::Vector2f(position.x * PPM,position.y * PPM), 1.0f, 0.05f, 0.5f);
				listadoExplosion.insert(nueva);
			}
			listadoBala.erase(dyingBala);
            delete dyingBala;
			dyingBala = NULL;
		}
		
		listaDeBalasPorEliminar.clear();
		
		//Eliminación de las explosiones
		set<Explosion*>::iterator itExplo = listaDeExploPorEliminar.begin();
		set<Explosion*>::iterator endExplo = listaDeExploPorEliminar.end();
		for(; itExplo!=endExplo; ++itExplo){
			Explosion* dyingExplo = *itExplo;
			listadoExplosion.erase(dyingExplo);
			delete dyingExplo;
			dyingExplo = NULL;
		}

		listaDeExploPorEliminar.clear();
		
        Ventana.clear(sf::Color::Black);
       
        world.Step(1.0f/60.0f, 10, 10);
        
        terra.Render(&Ventana);
		
		
		//Update y Render Balas
		itBala = listadoBala.begin();
		endBala = listadoBala.end();
		for(; itBala!=endBala; ++itBala){
			Bala* updateBala = *itBala;
			updateBala->Update_Shape();
			updateBala->Render(&Ventana);
		}
		
		//Update y Render Explosiones
		itExplo = listadoExplosion.begin();
		endExplo = listadoExplosion.end();
		for(; itExplo!=endExplo; ++itExplo){
			Explosion* updateExplo = *itExplo;
			updateExplo->Update();
			updateExplo->Render(&Ventana);
		}
		
        Ventana.display();
    }
    return 0;
}

//----------------------------------------------------------------------------------------Entidad
Entidad::Entidad(){}

string Entidad::getTipo(){
	return tipo;
}

//----------------------------------------------------------------------------------------Suelo

Suelo::Suelo(b2World *mundo){	
			tipo = "Suelo";

			b2BodyDef sueloBodyDef;
			sueloBodyDef.userData = this;
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
			
			m_Shape =  new sf::RectangleShape(sf::Vector2f(WIDTH, 100));
			m_Shape->setOrigin(WIDTH/2, 100/2);
			m_Shape->setPosition(sf::Vector2f(m_pBody->GetPosition().x*PPM, m_pBody->GetPosition().y*PPM));
			m_Shape->setFillColor(Color::Blue);
}

void Suelo::Render(sf::RenderWindow *window){
	window->draw(*m_Shape);
}

//----------------------------------------------------------------------------------------Explosion
Explosion::Explosion(b2World *mundo, sf::Vector2f position, float radio, float incremento, float inicial){
	tipo = "Explosion";
	
	radioActual = inicial;
	radioMax = radio;
	incrementoRadio = incremento;
	
	b2BodyDef exploBodyDef;
	exploBodyDef.userData = this;
	exploBodyDef.type = b2_staticBody;
	exploBodyDef.position.Set(position.x*MPP, position.y*MPP);
	m_pBody = mundo->CreateBody(&exploBodyDef);
	
	b2CircleShape exploCircle;
	exploCircle.m_p.Set(inicial,inicial);
	exploCircle.m_radius = inicial;
            
	b2FixtureDef exploFixtureDef;
	exploFixtureDef.shape = &exploCircle;
	exploFixtureDef.friction = 0.2f;
	exploFixtureDef.restitution = 0.3f;
	exploFixtureDef.density = 0.7f;
	exploFixtureDef.filter.categoryBits = CATEGORY_SCENERY;
	exploFixtureDef.filter.maskBits = MASK_SCENERY;

	m_pBody->CreateFixture(&exploFixtureDef);
	
	m_Shape =  new sf::CircleShape(inicial * PPM);
    m_Shape->setOrigin(radioActual * PPM, radioActual * PPM);
    m_Shape->setPosition(sf::Vector2f(m_pBody->GetPosition().x*PPM, m_pBody->GetPosition().y*PPM));
    m_Shape->setFillColor(Color::White);
}

void Explosion::Update(){
       
	if(radioActual < radioMax){
		if(frameCounter%10 == 0){
			radioActual = radioActual + incrementoRadio;

			b2Fixture *fixtureA = m_pBody->GetFixtureList();
			m_pBody->DestroyFixture(fixtureA);

			b2CircleShape circleShape;
			//circleShape.m_p.Set(radioActual, radioActual);
			circleShape.m_radius = radioActual;

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &circleShape;
			fixtureDef.friction = 0.2f;
			fixtureDef.restitution = 0.3f;
			fixtureDef.density = 0.7f;
			fixtureDef.filter.categoryBits = CATEGORY_SCENERY;
			fixtureDef.filter.maskBits = MASK_SCENERY;

			m_pBody->CreateFixture(&fixtureDef);

			float angle = m_pBody->GetAngle();
			b2Vec2 pos = m_pBody->GetPosition();

			m_Shape->setRadius(radioActual * PPM);
			m_Shape->setOrigin(radioActual * PPM, radioActual * PPM);
			m_Shape->setPosition(pos.x * PPM, pos.y * PPM);
			m_Shape->setRotation((angle*180)/M_PI);
		}
	}
	else{
		listaDeExploPorEliminar.insert(this);
	}

	
}

void Explosion::Render(sf::RenderWindow *window){
	window->draw(*m_Shape);
}

Explosion::~Explosion(){
	m_pBody->GetWorld()->DestroyBody(m_pBody);
	delete m_Shape;
	m_Shape = NULL;
}

//----------------------------------------------------------------------------------------Bala
Bala::Bala(b2World *mundo, sf::Vector2f size, sf::Vector2f position, bool explo){
	tipo = "Bala";
	explosion = explo;	
	
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

void Bala::Render(sf::RenderWindow *window){
	window->draw(*m_Shape);
}

Bala::~Bala(){
    m_pBody->GetWorld()->DestroyBody(m_pBody);
	delete m_Shape;
	m_Shape = NULL;
	//Hacer un delete de cada objeto que se ha creado con un New y luego igualarlo a NULL
}

//--------------------------------------------------------------------------------------ContactListener
void MyContactListener::BeginContact(b2Contact* contact){
            
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	
	Entidad* entidadA = static_cast<Entidad*>(bodyUserDataA);
	Entidad* entidadB = static_cast<Entidad*>(bodyUserDataB);
	
	cout << "BOOM colision - " << entidadA->getTipo() << " - " << entidadB->getTipo() << endl;
	
	//Colision con Balas
	if(entidadA->getTipo().compare("Bala") == 0 || entidadB->getTipo().compare("Bala") == 0){
		if(entidadA->getTipo().compare("Bala") == 0){
			Bala* bala = static_cast<Bala*>(bodyUserDataA);
			listaDeBalasPorEliminar.insert(bala);
		}
		else if(entidadB->getTipo().compare("Bala") == 0){
			Bala* bala = static_cast<Bala*>(bodyUserDataB);
			listaDeBalasPorEliminar.insert(bala);
		}
	}
	
	
}

void MyContactListener::EndContact(b2Contact* contact){}