
/* 
 * File:   Platform.h
 * Author: daniel
 *
 * Created on 26 de marzo de 2017, 14:03
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#include <vector>
#include "Entidad.h"
#include "motorfisico/Cuerpo.h"
#include "motorfisico/Motorfisico.h"
#include "motorgrafico/headerfiles/VisibleBody.h"

using namespace std;

class Platform : public Entidad {
public:

    Platform();
    Platform(const Platform& orig);
    Platform(float sizex, float sizey, float posx, float posy, float friction);

    VisibleBody* getBodyShape();

     void Contact(void* punt, string tipo);
    
    virtual ~Platform();
private:
    
    Cuerpo *cuerpo;
    VisibleBody *body;

};

#endif /* PLATFORM_H */