//
// Created by wojciech on 15.12.2019.
//

#include "Kabum.h"
#include "Audio.hpp"

Kabum::Kabum(sf::Vector2f position,float size,int obrazenia):
sprite(Layers::kabum),
size(size),
licznik(0)
{
    sprite.setAnimation(base.forceActor<AnimationBank>().get("maleboom.s1a"));
    sprite.setOrigin(sf::Vector2f(sprite.getAnimation()->getFrameSize()/2u));
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(size,size));
    base.forceActor<Audio>().playSound();
}

void Kabum::update()
{
    licznik++;
    if(licznik > 9){
        scene.deleteActor(*this);
        return;
    }
    //scene.deleteActor(*kule[k_i]);
}
sf::Vector2f Kabum::get_position()
{
    return sprite.getPosition();
}

AnimatedSprite* Kabum::get_asprite()
{
    return &sprite;
}



