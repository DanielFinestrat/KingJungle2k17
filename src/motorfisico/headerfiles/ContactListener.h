
/* 
 * File:   ContactListener.h
 * Author: daniel
 *
 * Created on 26 de marzo de 2017, 20:41
 */

#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <iostream>
#include "../../../Box2D/Box2D.h"
#include "../../headerfiles/Entidad.h"
#include "../../headerfiles/Trampa.h"

class ContactListener : public b2ContactListener {
public:
    
    /**
     * Función que se ejecuta al empezar una colisión en el mundo
     * @param contact b2Contact: Elemento con los cuerpos que intervienen en la colisión
     */
    void BeginContact(b2Contact* contact);
    
};

#endif /* CONTACTLISTENER_H */

