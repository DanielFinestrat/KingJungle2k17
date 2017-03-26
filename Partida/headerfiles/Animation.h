/* 
 * File:   Animation.h
 * Author: amygwyllion
 *
 * Created on 8 de marzo de 2017, 10:41
 */
/***************NOTAS******************/
/* a los punteros siempre les pondre el atributo const para que, aunque su valor cambie, su posicion en memoria no lo haga y el programa no crashee
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Animation {
public:
    Animation();
    Animation(const Animation& orig);
    virtual ~Animation();

    /** @fn <i>void</i> Animation::<b>setSpriteSheet</b>(<i>Texture&</i> <b>new_texture</b>)
     * 
     * Asigna un spritesheet
     * @param <i>Texture&</i> <b>texture</b> : referencia a un puntero tipo Texture donde se encuentra el nuevo spritesheet
     */
    void setSpriteSheet(const Texture&);

    /** @fn <i>Texture*</i> Animation::<b>getSpriteSheet</b>() 
     * 
     * Devuelve una textura con el spritesheet
     * @returns <i>Texture*</i> la textura con el spritesheet actual
     */
    const Texture* getSpriteSheet() const; //devuelve el spritesheet



    /**@fn <i>void</i> Animation::<b>addFrame</b>(<i>IntRect</i> <b>new_frame</b>)
     * 
     * Almacena un nuevo sprite dentro del vector frames para su posterior animacion.
     * @param <i>IntRect</i> <b>new_frame</b> : rectangulo del spritesheet donde se encuentra el nuevo sprite.
     */
    void addFrame(IntRect);

    /**@fn <i>IntRect&</i> Animation::<b>getFrame</b>( <i>size_t</i> <b>index</b>)
     * 
     * Busca un frame en la posicion pasada por parametro
     * @param <i>size_t</i> <b>index</b> : posicion en la que queremos buscar
     * @return <i>IntRect&</i> frame (rectangulo del spritesheet) que se encontraba en esa posicion. \n Si la posicion es menor que cero o mayor que el tamanyo de frames devolvera <i>NULL</i>;
     */
    const IntRect& getFrame(size_t) const;

    /**@fn <i>size_t</i> Animation::<b>getSize</b>()
     * 
     * Devuelve el tamaño del vector donde se almacenan los frames de la animacion.
     * @return <i>size_t</i> el tamaño actual del vector <b>frames</b> 
     */
    size_t getSize() const;

private:
    vector<IntRect> frames; /**<vector donde se almacenan todos los frames (IntRect) que contiene la animacion*/
    const Texture* texture; /**<parametro donde se guarda el spritesheet*/
};

#endif /* ANIMATION_H */

