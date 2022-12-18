#pragma once

#include "base/All.hpp"
#include "Animal.hpp"
#include <list>

void setupWinScreen(Scene& scene, Materia materia);

class WinScreen : public Actor{
public:
    WinScreen(Materia materia);
    virtual ~WinScreen();
    void update() override;

private:
    Sprite sprite;
    AnimatedSprite dance;
    std::list<FlyingAnimal*> animals;
    bool escPressedLastFrame;
};


