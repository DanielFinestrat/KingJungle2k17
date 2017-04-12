/* 
 * File:   sprite.h
 * Author: amygwyllion
 *
 * Created on 8 de marzo de 2017, 11:25
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;

class SpriteAnimated : public Drawable, public Transformable { //hereda de las clases Drawable y Transformable de SFML
public:

    explicit SpriteAnimated(Time, bool, bool);
    /*EXPLCIT significa que no puede haber otra instancia, ni haciendose con plantillas de clase ni inicianizandolo desde otro objeto*/
    explicit SpriteAnimated();
    SpriteAnimated(const SpriteAnimated& orig);
    virtual ~SpriteAnimated();
    void update(Time);
    void setAnimation(const Animation&);
    void setFrameTime(Time);
    void play();
    void play(const Animation&);
    void pause();
    void stop();
    void Loop(bool);
    void setColor(const Color&);
    const Animation* getAnimation() const;
    FloatRect getLocalBounds() const;
    FloatRect getGlobalBounds() const;
    bool isSpriteLooped() const;
    bool isSpritePlaying() const;
    Time getFrameTime() const;
    void setFrame(size_t, bool resetTime = true);

private:

    const Animation* animation;
    Time frameTime;
    Time currentTime;
    size_t currentFrame;
    bool isPaused;
    bool isLooped;
    const Texture* texture;
    Vertex vertex[4];

    virtual void draw(RenderTarget& target, RenderStates states) const;

};

#endif /* SPRITE_H */