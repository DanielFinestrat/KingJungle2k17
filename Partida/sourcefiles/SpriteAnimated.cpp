/* 
 * File:   sprite.cpp
 * Author: amygwyllion
 * 
 * Created on 8 de marzo de 2017, 11:25
 */

#include "../headerfiles/SpriteAnimated.h"

using namespace sf;
using namespace std;

SpriteAnimated::SpriteAnimated(Time m_frameTime, bool paused, bool looped) {
    animation = NULL;
    frameTime = m_frameTime;
    currentFrame = 0;
    isPaused = paused;
    isLooped = looped;
    texture = NULL;

}

SpriteAnimated::SpriteAnimated() {
}

SpriteAnimated::SpriteAnimated(const SpriteAnimated& orig) {
}

SpriteAnimated::~SpriteAnimated() {
}

void SpriteAnimated::setAnimation(const Animation& m_animation) {
    animation = &m_animation;
    texture = animation->getSpriteSheet();
    currentFrame = 0;
    setFrame(currentFrame);
}

void SpriteAnimated::setFrameTime(Time time) {
    frameTime = time;
}

void SpriteAnimated::play() {
    isPaused = false;
}

void SpriteAnimated::pause() {
    isPaused = true;
}

void SpriteAnimated::stop() {
    isPaused = true;
    currentFrame = 0;
    setFrame(currentFrame);
}

void SpriteAnimated::play(const Animation& m_animation) {
    if (getAnimation() != &m_animation)
        setAnimation(m_animation);
    play();
}

void SpriteAnimated::Loop(bool looped) {
    isLooped = looped;
}

void SpriteAnimated::setColor(const Color& m_color) {
    vertex[0].color = m_color;
    vertex[1].color = m_color;
    vertex[2].color = m_color;
    vertex[3].color = m_color;
}

const Animation* SpriteAnimated::getAnimation() const {
    return animation;
}

FloatRect SpriteAnimated::getLocalBounds() const {
    IntRect rect = animation->getFrame(currentFrame);

    float width = static_cast<float> (abs(rect.width));
    float height = static_cast<float> (abs(rect.height));

    return FloatRect(0.f, 0.f, width, height);
}

FloatRect SpriteAnimated::getGlobalBounds() const {
    return getTransform().transformRect(getLocalBounds());
}

bool SpriteAnimated::isSpriteLooped() const {
    return isLooped;
}

bool SpriteAnimated::isSpritePlaying() const {
    return !isPaused; /*basicamente, si isPaused es false significa que se está reproduciendo, por lo tanto ha de devolver true*/
}

Time SpriteAnimated::getFrameTime() const {
    return frameTime;
}

void SpriteAnimated::setFrame(size_t newFrame, bool resetTime) {
    if (animation) {
        //calculamos las coordenadas de las texturas
        IntRect rect = animation->getFrame(newFrame);

        vertex[0].position = Vector2f(0.f, 0.f);
        vertex[1].position = Vector2f(0.f, static_cast<float> (rect.height));
        vertex[2].position = Vector2f(static_cast<float> (rect.width), static_cast<float> (rect.height));
        vertex[3].position = Vector2f(static_cast<float> (rect.width), 0.f);

        float left = static_cast<float> (rect.left) + 0.0001f;
        float right = left + static_cast<float> (rect.width);
        float top = static_cast<float> (rect.top);
        float bottom = top + static_cast<float> (rect.height);

        vertex[0].texCoords = Vector2f(left, top);
        vertex[1].texCoords = Vector2f(left, bottom);
        vertex[2].texCoords = Vector2f(right, bottom);
        vertex[3].texCoords = Vector2f(right, top);
    }

    if (resetTime)
        currentTime = Time::Zero;
}

void SpriteAnimated::update(Time deltaTime) {
    // si no esta pausado tenemos una animacion valida
    if (!isPaused && animation) {
        // anyadimos delta time
        currentTime += deltaTime;

        // si el tiempo actual es mayor entonces la animacion avanza un frame
        if (currentTime >= frameTime) {
            // reseteamos el tiempo pero nos quedamos con la diferencia
            currentTime = microseconds(currentTime.asMicroseconds() % frameTime.asMicroseconds());

            // cogemos el indice del siguiente frame
            if (currentFrame + 1 < animation->getSize())
                currentFrame++;
            else {
                //si la animacion ya ha acabado reseteamos a 0 
                currentFrame = 0;

                if (!isLooped) {
                    isPaused = true;
                }

            }

            // actualizamos el frame actual sin resetear el tiempo
            setFrame(currentFrame, false);
        }
    }
}

void SpriteAnimated::draw(RenderTarget& target, RenderStates states) const {
    if (animation && texture) {
        states.transform *= getTransform();
        states.texture = texture;
        target.draw(vertex, 4, Quads, states);
    }
}