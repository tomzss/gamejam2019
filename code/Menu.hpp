#pragma once

#include "base/All.hpp"

void setupMainMenu(Scene& scene);

class Menu: public Actor{
public:
    Menu();
    void update() override;

private:
    Sprite sprite;
    AnimatedSprite zolw;
    bool enterPressedLastFrame;
    bool escPressedLastFrame;
};

