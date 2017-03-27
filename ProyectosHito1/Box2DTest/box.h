#ifndef BOX_H_
#define BOX_H_
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Color randColor();

class CBox{
    private:
       b2Body * m_body; //Se le aplican fuerzas, velocidad, posición...
       b2BodyDef m_bodyDef; //Donde se almacenan variables
       b2PolygonShape m_bodyShape; //El collider
       b2FixtureDef m_bodyFix; //Donde se almacenan constantes
       RectangleShape m_shape; //Shape de sfml
       static int n;
    public:
       CBox(b2World & world);
       CBox();
       void SetWorld(b2World & world);
       b2Body* GetBody();
       Shape & GetShape();
       void update();
       void ResetPosition(b2World & world);
       void jump();
       void move(float direction);
       void setN(int newN) {n = newN;}
       int getN() {return n;}
       ~CBox();
};

#endif