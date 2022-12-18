#pragma once

#include "base/All.hpp"
#include "Enums.hpp"

class Animal : public Actor{
public:
    explicit Animal(const sf::Vector2f& position);
    void setAnimation(const sf::String& filename);
    Animal_type get_A_type();
    sf::Vector2f getPosition();
    void scale(float);
    Materia get_material();
    AnimatedSprite *get_asprite();
    void set_matirial(Materia materia_new);

protected:
    AnimatedSprite sprite;
    Materia materia;
    Animal_type animal_t;

    static const float marginToTarget;
    static const float speed;
};

class FlyingAnimal : public Animal{
public:
    explicit FlyingAnimal(const sf::Vector2f& position);
    void update() override;


private:
    void randTarget();

    sf::Vector2f target;
    sf::Vector2f direction ;
    bool first_time;
};

class WalkingAnimal : public Animal{
public:
    explicit WalkingAnimal(const sf::Vector2f& position, const float way);
    void update() override;


private:
    void randTarget();

    sf::Vector2f pos ;
    float target;
    float road;
    bool first_time;
};
