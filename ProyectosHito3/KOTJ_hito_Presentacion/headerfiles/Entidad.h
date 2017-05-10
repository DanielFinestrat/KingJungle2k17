
/* 
 * File:   Entidad.h
 * Author: daniel
 *
 * Created on 26 de marzo de 2017, 13:57
 */

#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <string>
using namespace std;

#define PPM 64.0f 
#define MPP (1.0f/PPM)

#define pSize 64

const short CATEGORY_BULLET = 0x0001;
const short CATEGORY_SCENERY = 0x0002;
const short CATEGORY_PLAYER = 0x0004;
const short CATEGORY_GUN = 0x0008;
const short CATEGORY_EXPLOSION = 0x0016;
const short CATEGORY_TRAMPA = 0x0032;

const short MASK_BULLET = CATEGORY_SCENERY | CATEGORY_PLAYER;
const short MASK_PLAYER = CATEGORY_BULLET | CATEGORY_SCENERY | CATEGORY_TRAMPA;
const short MASK_GUN = CATEGORY_SCENERY;
const short MASK_SCENERY = -1;
const short MASK_EXPLOSION = CATEGORY_PLAYER;
const short MASK_TRAMPA1 = CATEGORY_PLAYER;
const short MASK_TRAMPA2 = CATEGORY_PLAYER | CATEGORY_BULLET;

class Entidad {
public:
    string tag;
    
    Entidad();
    Entidad(const Entidad& orig);
    
    virtual void Render();
    virtual void Contact(void* punt, string tipo);
    
    string getTag();
    
    virtual ~Entidad();
private:

};

#endif /* ENTIDAD_H */