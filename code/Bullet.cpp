#include "Bullet.hpp"
#include "Terrain.hpp"

const float Bullet::speed = 60;

void Bullet::update(){
    sprite.move(movement);
    auto& terrain = scene.forceActor<Terrain>();
    if(sprite.getPosition().x < 0
    || sprite.getPosition().y < 0
    || sprite.getPosition().x > terrain.getWorldSize().x
    || sprite.getPosition().y > terrain.getWorldSize().y)
        scene.deleteActor(*this);
    // TODO: jeśli w coś trafi to ...
}

sf::Vector2f Bullet::directVector(Direction direction, float vecLength){
    switch(direction){
    case Direction::left:  return sf::Vector2f(-vecLength, 0);
    case Direction::right: return sf::Vector2f(vecLength, 0);
    case Direction::up:    return sf::Vector2f(0, -vecLength);
    case Direction::down:  return sf::Vector2f(0, vecLength);
    default: assert(false); // invalid enum
    }
}

Bullet::Bullet(const sf::Vector2f& position, Direction direction, Materia materia)
    : sprite(Layers::bullet)
    , movement(directVector(direction, speed))
    , materia(materia){
    sprite.setPosition(position);
    if(materia==Materia::normal)
        sprite.setAnimation(base.forceActor<AnimationBank>().get("animacjapocisk1.s1a"));
    else
        sprite.setAnimation(base.forceActor<AnimationBank>().get("animacjapocisk2.s1a"));
    sprite.setOrigin(sf::Vector2f(sprite.getAnimation()->getFrameSize()/2u));
}

const Materia Bullet::getMateria() const{
    return materia;
}

sf::Vector2f Bullet::get_Position()
{
    return sprite.getPosition();
}
