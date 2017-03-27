#include <sstream>
#include <ctime>
#include <stdio.h>
#include "Box2D/Box2D.h"
#include "Box2D/Weapon.h"



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

set<Bala*> listaDeBalasPorEliminar;
set<Bala*> listadoBala;

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

/******************************************************************************
************************** CLASS MY CONTACT LISTENER **************************
*******************************************************************************/

class MyContactListener : public b2ContactListener{
    public:
        void BeginContact(b2Contact* contact); 

        void EndContact(b2Contact* contact);
};



/*******************************************************************************/


int main() {
    
    //Definir mundo Box2D
    b2Vec2 gravity(0.0f, 9.8f);
    b2World *world = new b2World(gravity);
   
    Suelo floor(world);
    
    //Definir arma
    Weapon *weapon = new Weapon(world, Vector2f(100,30), Vector2f(WIDTH/2,200), 60.0f/60.0f, 1);
    
    //Crear ventana
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Prueba disparo arma");
    window.setFramerateLimit(60);
    
    //Contador y variable booleana para controlar la cadencia de disparo
    float cont = 60.0;
    bool enableShoot;
    
    while(window.isOpen()) {
        if (cont == 60.0f*weapon->shootCadence) enableShoot = true;

        Event event;
        while(window.pollEvent(event)) {
            switch(event.type){
                case Event::Closed:
                    window.close();
                    break;
                    
                case Event::KeyReleased:
                    switch(event.key.code) {
                        case Keyboard::Space:
                            if (enableShoot){
                                
                                weapon->shoot(world);
                                
                                enableShoot = false;
                                cont = 0;
                            }
                            break;
                    }
                    break;
            }
        }
        cont++;

        //Creamos iteradores para recorrer los vectores de balas
        set<Bala*>::iterator it = weapon->balasAEliminar.begin();
        set<Bala*>::iterator end = weapon->balasAEliminar.end();
        
        
        //Recorremos los vectores de balas
        for(; it != end; ++it) {
            cout << "Eliminando bala" << endl;
            Bala* dyingBala = *it; //Asignamos la bala del vector a una bala (que morira muajaja)
            weapon->listadoBalas.erase(dyingBala); //La eliminamos del vector
            delete dyingBala; //Eliminamos la bala
            dyingBala = NULL; //Dejamos el puntero a NULL
            weapon->balasAEliminar.clear(); //Limpiamos el vector
        }
        
        window.clear(Color::Black);
        
        //World step y render del suelo
        world->Step(1.0f/60.0f, 10, 10);
        window.draw(floor.m_Shape);
        
        //Update y render del arma
        weapon->update();
        weapon->render(&window);
        
        
        //Update y render de las balas
        it = weapon->listadoBalas.begin();
        end = weapon->listadoBalas.end();
        
        for(; it != end; ++it) {
            
            Bala* updateBala = *it; //Asignamos la bala a actualizar
            updateBala->Update_Shape(weapon->balasAEliminar);
            updateBala->Render(&window);
        }
        
        window.display();
    }
    return 0;
}