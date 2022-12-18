//
// Created by wojciech on 15.12.2019.
//

#ifndef GJ_KABUM_H
#define GJ_KABUM_H

#include "base/All.hpp"


class Kabum : public Actor{
public:
    Kabum(sf::Vector2f position,float size,int obrazenia);
    void update() override;
    AnimatedSprite sprite;
    sf::Vector2f get_position();
    AnimatedSprite* get_asprite();
private:
    float size;
    int licznik;

};


#endif //GJ_KABUM_H
