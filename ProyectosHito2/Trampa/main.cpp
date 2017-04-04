#include <sstream>
#include <stdio.h>
#include "Box2D/Box2D.h"
#include "Trampa.h"
#include "ContactListener.h"
#include <SFML/Graphics.hpp>




#define WIDTH 800 
#define HEIGHT 600
#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL
#define DEGTORAD 0.0174532925199432957;


short CATEGORY_SCENERY = 0x0002;
short CATEGORY_PJ = 0x0004;
short CATEGORY_TRAMPA = 0x0001;


short MASK_TRAMPA = CATEGORY_PJ;
short MASK_PJ = CATEGORY_SCENERY | CATEGORY_TRAMPA;
short MASK_SCENERY = -1;




using namespace std;
using namespace sf;

/*
 * =============================================================================
 *                          STRUCT SUELO (CAJAS)
 * =============================================================================
 */

struct Suelo {

    Suelo(b2World *mundo) {

        b2BodyDef sueloBodyDef;
        sueloBodyDef.position.Set(WIDTH / 2 * MPP, (HEIGHT) * MPP);
        m_pBody = mundo->CreateBody(&sueloBodyDef);

        b2PolygonShape sueloBox;
        sueloBox.SetAsBox(WIDTH / 2 * MPP, 100.0f / 2 * MPP);

        b2FixtureDef sueloFixtureDef;
        sueloFixtureDef.shape = &sueloBox;
        sueloFixtureDef.friction = 0.8f;
        sueloFixtureDef.restitution = 0.3f;
        sueloFixtureDef.density = 0.7f;
        sueloFixtureDef.filter.categoryBits = CATEGORY_SCENERY;
        sueloFixtureDef.filter.maskBits = MASK_SCENERY;

        m_pBody->CreateFixture(&sueloFixtureDef);

        m_Shape = sf::RectangleShape(sf::Vector2f(WIDTH, 100));
        m_Shape.setOrigin(WIDTH / 2, 100 / 2);
        m_Shape.setPosition(sf::Vector2f(m_pBody->GetPosition().x*PPM, m_pBody->GetPosition().y * PPM));
        m_Shape.setFillColor(Color::Blue);
    }

    b2Body *m_pBody;
    sf::RectangleShape m_Shape;
};

struct Pared1 {

    Pared1(b2World *mundo, float x) {

        b2BodyDef paredBodyDef;
        paredBodyDef.position.Set((50 / 2 + x) * MPP, HEIGHT / 2 * MPP);
        m_pBody = mundo->CreateBody(&paredBodyDef);

        b2PolygonShape paredBox;
        paredBox.SetAsBox((50 / 2) * MPP, HEIGHT / 2 * MPP);

        b2FixtureDef paredFixtureDef;
        paredFixtureDef.shape = &paredBox;
        paredFixtureDef.friction = 0;
        paredFixtureDef.restitution = 0;
        paredFixtureDef.density = 0.7f;
        paredFixtureDef.filter.categoryBits = CATEGORY_SCENERY;
        paredFixtureDef.filter.maskBits = MASK_SCENERY;

        m_pBody->CreateFixture(&paredFixtureDef);

        m_Shape = sf::RectangleShape(sf::Vector2f(50, HEIGHT));
        m_Shape.setOrigin(50 / 2, HEIGHT / 2);
        m_Shape.setPosition(sf::Vector2f(m_pBody->GetPosition().x*PPM, m_pBody->GetPosition().y * PPM));
        m_Shape.setFillColor(Color::Green);
    }

    b2Body *m_pBody;
    sf::RectangleShape m_Shape;
};
//=============================================================================



/*
 * =============================================================================
 *                           STRUCT PERSONAJE
 * =============================================================================
 */


struct pjBox {
    int dir; //Puede ser 1 o -1 (derecha e izquierda respectivamente)
    b2Body *m_pBody;
    sf::RectangleShape m_Shape;
    bool contact;
   

    pjBox(b2World *world) {
        b2BodyDef pjBodyDef;
        pjBodyDef.userData = this;
        pjBodyDef.type = b2_dynamicBody;
        pjBodyDef.position.Set(WIDTH / 2 * MPP, HEIGHT / 2 * MPP);
        m_pBody = world->CreateBody(&pjBodyDef);

        b2PolygonShape pjBox;
        pjBox.SetAsBox(60 / 2 * MPP, 100 / 2 * MPP);

        b2FixtureDef pjFixtureDef;
        pjFixtureDef.shape = &pjBox;
        pjFixtureDef.friction = 0.2f;
        pjFixtureDef.restitution = 0.3f;
        pjFixtureDef.density = 0.1f;
        pjFixtureDef.filter.categoryBits = CATEGORY_PJ;
        pjFixtureDef.filter.maskBits = MASK_PJ;

        m_pBody->CreateFixture(&pjFixtureDef);

        m_Shape = sf::RectangleShape(sf::Vector2f(30, 100));
        m_Shape.setOrigin(sf::Vector2f(30 / 2, 100 / 2));
        m_Shape.setPosition(sf::Vector2f(m_pBody->GetPosition().x, m_pBody->GetPosition().y));
        m_Shape.setFillColor(sf::Color::Red);
        
        dir=1;
    }
};
//=============================================================================

/*
 * =============================================================================
 *                          FUNCIONES DEL PERSONAJE
 * =============================================================================
 */

void updatePJ(pjBox *player) {
    b2Vec2 pos = player->m_pBody->GetPosition();

    player->m_pBody->SetTransform(pos, 0);
    player->m_Shape.setPosition(pos.x * PPM, pos.y * PPM);

}

//Movimiento del personaje, sencillo aplicando una fuerza a izquierda o derecha (-1 o 1)

void move(int dir, pjBox *player) {
    int vel = player->m_pBody->GetLinearVelocity().x;
    int prevdir = vel > 0 ? 1 : -1;

    //cout << dir << ", "<< prevdir<<endl;
    if (vel < 4.5 && vel > -4.5 || dir != prevdir) {
        player->m_pBody->ApplyForce(b2Vec2(5.0f * dir, 0), player->m_pBody->GetWorldCenter(), 1);

    }
}
void startContact(pjBox *player){ player->contact = true;}
void endContact(pjBox *player){player->contact = false;}

//Coger el arma
//Modificar para comprobar si tiene ya un arma y la cambie por la que esta en el suelo


//=============================================================================

/*
 *=============================================================================
 *                          CUERPO PRINCIPAL              
 *=============================================================================
 */
int main() {

    //Definir mundo Box2D
    b2Vec2 gravity(0.0f, 9.8f);
    b2World *world = new b2World(gravity);
   
    ContactListener escuchador;

    //Definir suelo, trampa y personaje
    Suelo floor(world);
    Pared1 paredL(world, 0);
    Pared1 paredR(world, WIDTH - 50);
    pjBox *player= new pjBox(world);
    sf::Vector2f trapSize(75,100); 
    sf::Vector2f trapPos(200 ,600);
    
    Trampa trampa1(world, trapSize, trapPos, 0, 0);

    //Crear ventana
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Prueba disparo arma");
    window.setFramerateLimit(60);

    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;

                case Event::KeyPressed:
                    switch (event.key.code) {
                        
                        case Keyboard::Escape:
                            window.close();
                            break;

                        case Keyboard::Left:
                            move(-1, player);
                            player->dir=-1;
                            break;

                        case Keyboard::Right:
                            move(1, player);
                            player->dir=1;
                            break;
                        case Keyboard::A:
                            trampa1.activar();
                            break;
                        case Keyboard::D:
                            trampa1.desactivar();
                            break;
                    }
                case Event::KeyReleased:
                    switch (event.key.code) {
                     
                    }
            }
        }

        // Partida - Eliminar objetos ---------------------------------------------------------------------------------  ------------------------------------------------------------

       window.clear(Color::Black);
       
        //World step y render del suelo
        world->Step(1.0f / 60.0f, 10, 10);
        world->SetContactListener(&escuchador);
        window.draw(floor.m_Shape);
        window.draw(paredL.m_Shape);
        window.draw(paredR.m_Shape);

        //Update del personaje

        updatePJ(player);
        
        window.draw(player->m_Shape);

        //-------------------------------------------------------------------------------
        //Update y render del arma, segun si esta en posesion o no
        trampa1.updateShape();
        
        trampa1.render(&window);
       
        //-------------------------------------------------------------------------------

        window.display();

    }
    return 0;
}