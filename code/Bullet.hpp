#pragma once

#include "base/All.hpp"
#include "Enums.hpp"

class Bullet : public Actor{
public:
    Bullet(const sf::Vector2f& position, Direction direction, Materia materia);
    void update() override;
    sf::Vector2f get_Position();
    const Materia getMateria() const;
    //Materia get_materia();

private:
    AnimatedSprite sprite;
    sf::Vector2f movement;
    const Materia materia;

    static const float speed;

    static sf::Vector2f directVector(Direction direction, float vecLength);
};
