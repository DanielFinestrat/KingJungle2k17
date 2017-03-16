#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include "Box2D/Box2D.h"
#include "box.h"

const int PPM = 30; //Pixel Por Metro, Box2D Trabaja en metro

using namespace std;
using namespace sf;

struct body{
    b2BodyDef DEF;
    b2PolygonShape SHAPE;
    b2FixtureDef FIX;
    b2Body * BOD;
    RectangleShape RECT;
};

//modifies to float by BHN
string floatToStr(float number);
float framesPS(Clock &);

int main() {
    RenderWindow app(VideoMode(800,600,32),"Application");

    b2Vec2 gravity(0.0f, 9.8f); //Gravedad para el world
    b2World world(gravity); //Lo primero q hay q crear es un world, y aplicarle gravedad

    Font myFont;
    if (!myFont.loadFromFile("./resources/bits.ttf")) return EXIT_FAILURE;
    Text text("FPS", myFont);
    text.setCharacterSize(20);
    text.setColor(Color(0, 255, 255, 255));
    text.setPosition(25,25);
    Text clearInstructions("[Space]", myFont);
    Text jumpInstructions("[UP][RIGHT][LEFT]", myFont);
    clearInstructions.setCharacterSize(18);
    jumpInstructions.setCharacterSize(18);
    clearInstructions.setColor(Color(200, 55, 100, 255));
    jumpInstructions.setColor(Color(200, 55, 100, 255));
    clearInstructions.setPosition(25, 50);
    jumpInstructions.setPosition(25, 70);

    float timeStep = 1 / 180.0f;
    Event event = Event();
    Clock clock;

    Clock fpsClock;
    int frameNumber = 0;
    int lastFPSFrame = 0;
    string lastFPSDisplay;
    
    const int boxes = 10;
    CBox good[boxes];
    int i = 0;
    for(i; i < boxes; i++) good[i].SetWorld(world);
    
    body ground;
    ground.DEF.position.Set(400.0f/PPM,600.0f/PPM);
    ground.RECT = RectangleShape(Vector2f(8000,25));
    ground.RECT.setOrigin(4000,25);
    ground.RECT.setFillColor(Color(200,75,20,255));
    ground.SHAPE.SetAsBox(4000.0f/PPM,25.0f/PPM);
    ground.BOD = world.CreateBody(&ground.DEF);
    ground.FIX.shape = &ground.SHAPE;
    ground.FIX.density = .7f;
    ground.FIX.friction = .5f;
    ground.BOD->CreateFixture(&ground.FIX);
    ground.RECT.setPosition(ground.BOD->GetPosition().x*PPM,ground.BOD->GetPosition().y*PPM);
    
    body leftWall;
    leftWall.DEF.position.Set(0.0f/PPM,-300/PPM);
    leftWall.RECT = RectangleShape(Vector2f(25,8000));
    leftWall.RECT.setOrigin(0,4000);
    leftWall.RECT.setFillColor(Color(200,75,200,255));
    leftWall.SHAPE.SetAsBox(25.0f/PPM,4000.0f/PPM);
    leftWall.BOD = world.CreateBody(&leftWall.DEF);
    leftWall.FIX.shape = &leftWall.SHAPE;
    leftWall.FIX.density = .7f;
    leftWall.FIX.friction = .9f;
    leftWall.BOD->CreateFixture(&leftWall.FIX);
    leftWall.RECT.setPosition(leftWall.BOD->GetPosition().x*PPM, leftWall.BOD->GetPosition().y*PPM);   

    body rightWall;
    rightWall.DEF.position.Set(800.0f/PPM,-300/PPM);
    rightWall.RECT = RectangleShape(Vector2f(25,8000));//100-50? is size?
    rightWall.RECT.setOrigin(25,4000);
    rightWall.RECT.setFillColor(Color(100,205,20,255));
    rightWall.SHAPE.SetAsBox(25.0f/PPM,4000.0f/PPM);
    rightWall.BOD = world.CreateBody(&rightWall.DEF);
    rightWall.FIX.shape = &rightWall.SHAPE;
    rightWall.FIX.density = .7f;
    rightWall.FIX.friction = .9f;
    rightWall.BOD->CreateFixture(&rightWall.FIX);
    rightWall.RECT.setPosition(rightWall.BOD->GetPosition().x*PPM, rightWall.BOD->GetPosition().y*PPM);            
    
    while(app.isOpen()){
        world.Step(timeStep, 8, 3); //Un paso de tiempo timeStep, se calcula la velocidad 8 veces y el tiempo 3  
        char buff[32];
        text.setString("FPS: " + String(buff));

        frameNumber++;
        if (fpsClock.getElapsedTime().asMilliseconds() > 1000) {
            char buf[64];
            lastFPSDisplay = string(buf);
            lastFPSFrame = frameNumber;
            fpsClock.restart();
            fflush(stdout);
        }

        Event events;
        while (app.pollEvent(events)) {
            switch (events.type) {
            case Event::Closed:
                app.close();
                break;
            case Event::KeyPressed:
                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    app.clear();
                    app.display();
                    good->setN(0);
                    for(int i = 0; i < boxes; i++) {
                        good[i].ResetPosition(world);
                    }
                }
                
                else if (Keyboard::isKeyPressed(Keyboard::Escape))
                    app.close();
                else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    for(int i = 0; i < boxes; i++) {
                        good[i].jump();
                    }
                }
                
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    for(int i = 0; i < boxes; i++) {
                        good[i].move(1);
                    }
                }
                else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    for(int i = 0; i < boxes; i++) {
                        good[i].move(-1);
                    }
                }
                break;
            }
        }

        for(int i = 0; i < boxes; i++) {
            good[i].update();
        }

        app.clear();
        app.draw(ground.RECT);
        app.draw(leftWall.RECT);
        app.draw(rightWall.RECT);
        app.draw(text);
        app.draw(clearInstructions);
        app.draw(jumpInstructions);
        for(int i = 0; i < boxes; i++) app.draw(good[i].GetShape());
        app.display();
    }

    return 0;
}

float framesPS(Clock & clock){
    bool sec = false;
    int count = 0;
    count++;
    if(clock.getElapsedTime().asMilliseconds() >= 1000){
        sec = true;
        clock.restart();
        count = 0;
    }
    
    float t = (float)clock.getElapsedTime().asMilliseconds();
    float ret = 0;
    if ( t ==  0 ) return 0;
    else {ret = count / (float)clock.getElapsedTime().asMilliseconds(); }
    if ( sec){
        char buf[64];
        fflush(stdout);
    }
    return ret;
}