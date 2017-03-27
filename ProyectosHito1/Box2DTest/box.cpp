#include "box.h"
#include <iostream>
using namespace sf;
using namespace std;

const int PPM = 30;
int CBox::n = 0;

CBox::CBox(b2World & world) {
    m_shape = RectangleShape(Vector2f(20,20));
    m_shape.setOrigin(10,10);
    m_shape.setFillColor(Color(255, 0, 255, 255));
    m_bodyDef.position.Set(300.0f/PPM,-300.0f/PPM-n*5/PPM);
    m_bodyDef.type = b2_dynamicBody;
    m_bodyShape.SetAsBox(10.0f/PPM,10.0f/PPM);
    m_bodyFix.shape = &m_bodyShape;
    m_bodyFix.density = 0.3f;
    m_bodyFix.friction = 0.5f;
    m_body = world.CreateBody(&m_bodyDef);
    m_body->CreateFixture(&m_bodyFix);
}

void CBox::SetWorld(b2World & world) {
    m_body = world.CreateBody(&m_bodyDef);
    m_body->CreateFixture(&m_bodyFix);
}

CBox::CBox() {
    m_shape = RectangleShape(Vector2f(10.f,10.f));
    m_shape.setOrigin(5,5);
    m_shape.setFillColor(randColor());
    m_bodyDef.position.Set(300.0f/PPM,-300.0f/PPM-n*5/PPM);
    n++;
    m_bodyDef.type = b2_dynamicBody;
    m_bodyShape.SetAsBox(5.0f/PPM,5.0f/PPM);
    m_bodyFix.shape = &m_bodyShape;
    m_bodyFix.density = 0.1f;
    m_bodyFix.friction = 0.1f;
}

b2Body* CBox::GetBody() {
    return m_body;
}

Shape & CBox::GetShape() {
    return m_shape;
}

void CBox::update() {
    m_body->SetTransform(m_body->GetPosition(),0);
    m_shape.setRotation(m_body->GetAngle());
    m_shape.setPosition(m_body->GetPosition().x*PPM, m_body->GetPosition().y*PPM);
    m_bodyDef.position.Set(m_shape.getPosition().x, m_shape.getPosition().y);
}

void CBox::ResetPosition(b2World & world) {
    m_body->DestroyFixture(m_body->GetFixtureList());
    world.DestroyBody(m_body);
    
    n++;
    m_bodyDef.position.Set(300.0f/PPM,-300.0f/PPM-n*5/PPM);
    m_bodyDef.angularVelocity = 0;
    m_bodyDef.linearVelocity.Set(0, 60);
    SetWorld(world);
    update();
}

void CBox::jump() {
    m_body->ApplyForce(b2Vec2(0,-10), m_body->GetWorldCenter(), 1);
    //m_body->SetLinearVelocity(b2Vec2(0,-5));
}

void CBox::move(float direction){
    m_body->ApplyForceToCenter(b2Vec2(direction*5, 0), 1);
}

CBox::~CBox(){}

Color randColor() {
    srand (time(NULL));
    int colorR = rand() % 255;
    int colorG = rand() % 255;
    int colorB = rand() % 255;
    return Color(colorR, colorG, colorB);
}