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
short CATEGORY_PJ = 0x0004;

short MASK_BALA = CATEGORY_SCENERY;
short MASK_PJ = CATEGORY_SCENERY;
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

struct pjBox {
    
    int dir; //Puede ser 1 o -1 (derecha e izquierda respectivamente)
    b2Body *m_pBody;
    sf::RectangleShape m_Shape;
    
    pjBox (b2World *world) {
        b2BodyDef pjBodyDef;
        pjBodyDef.type = b2_dynamicBody;
        pjBodyDef.position.Set(WIDTH/2*MPP, HEIGHT/2*MPP);
        m_pBody = world->CreateBody(&pjBodyDef);

        b2PolygonShape pjBox;
        pjBox.SetAsBox(60/2*MPP, 100/2*MPP);

        b2FixtureDef pjFixtureDef;
        pjFixtureDef.shape = &pjBox;
        pjFixtureDef.friction = 0.2f;
        pjFixtureDef.restitution = 0.3f;
        pjFixtureDef.density = 0.1f;
        pjFixtureDef.filter.categoryBits = CATEGORY_PJ;
        pjFixtureDef.filter.maskBits = MASK_PJ;

        m_pBody->CreateFixture(&pjFixtureDef);

        m_Shape = sf::RectangleShape(sf::Vector2f(30, 100));
        m_Shape.setOrigin(sf::Vector2f(30/2, 100/2));
        m_Shape.setPosition(sf::Vector2f(m_pBody->GetPosition().x, m_pBody->GetPosition().y));
        m_Shape.setFillColor(sf::Color::Red);
    }    
};

void updatePJ(pjBox &player) {
    b2Vec2 pos = player.m_pBody->GetPosition();
    
    player.m_pBody->SetTransform(pos,0);
    player.m_Shape.setPosition(pos.x * PPM, pos.y * PPM);
    
}

//Movimiento del personaje, sencillo aplicando una fuerza
void move(int dir, b2Body *body){
    body->ApplyForce(b2Vec2(5.0f*dir, 0),body->GetWorldCenter(),1);
}

//Coger el arma
void pickUp(pjBox player, Weapon *weapon) {
    if (player.m_Shape.getGlobalBounds().intersects(weapon->m_Shape->getGlobalBounds())) { //Comprobamos si intersectan sus formas
        weapon->inPossession = true;
        weapon->m_pBody->SetAwake(true);     
    } 
}

//Dejar el arma
void drop(pjBox player, Weapon *weapon) {
    if (player.m_Shape.getGlobalBounds().intersects(weapon->m_Shape->getGlobalBounds()) && weapon->inPossession) {//Comprobamos si intersectan sus formas y si tiene el arma
        weapon->inPossession = false;
        weapon->m_pBody->SetAwake(true);
    }
}

int main() {
    
    //Definir mundo Box2D
    b2Vec2 gravity(0.0f, 9.8f);
    b2World *world = new b2World(gravity);
   
    Suelo floor(world);
    pjBox player(world);
    
    //Definir arma
    Weapon *weapon = new Weapon(world, Vector2f(100,30), Vector2f(WIDTH/2,200), 1.0f, 1);
    
    //Crear ventana
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Prueba disparo arma");
    window.setFramerateLimit(60);
    
    //Variable de tiempo para controlar la cadencia de disparo
    Clock deltaClock;
    int difTime = 0;
    Time dt;
    time_t lastShot = time(&lastShot);
    
    while(window.isOpen()) {

        Event event;
        while(window.pollEvent(event)) {
            switch(event.type){
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    switch(event.key.code){
                        case Keyboard::Space:
                            if (weapon->inPossession) {
                                dt = deltaClock.restart();
                                difTime += dt.asMilliseconds();

                                if (difTime >= (1/weapon->shootCadence) * 1000) {
                                    difTime = 0.0;
                                    weapon->shoot(world, player.dir);
                                    lastShot = time(NULL);
                                
                                }
                            }
                        break;
                            
                        case Keyboard::Left:
                            move(-1, player.m_pBody);
                            player.dir = 1;
                            break;
                            
                        case Keyboard::Right:
                            move(1, player.m_pBody);
                            player.dir = -1;
                            break;
                    }
                case Event::KeyReleased:
                    switch(event.key.code){
                        case 27: //Tecla 1
                            pickUp(player, weapon);
                            break;
                            
                        case 28: //Tecla 2
                            drop(player,weapon);
                            break;
                    }
            }
        }

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
        
        updatePJ(player);
        window.draw(player.m_Shape);
        
        
        //Update y render del arma
        if (weapon->inPossession)
            weapon->update(player.m_pBody->GetPosition());
        else
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