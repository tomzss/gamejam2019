
#pragma once

#include "base/All.hpp"
#include "Enums.hpp"

struct KeyboardSet{
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key shoot;
};

class Player : public Actor{
public:
    Player(const sf::Vector2f& position, KeyboardSet keyboardSet, Materia materia);
    void setAnimation(const sf::String& filename);
    void update() override;
    [[nodiscard]] sf::Vector2f getCenterPosition() const;
    [[nodiscard]] const AnimatedSprite& getSprite() const;
    AnimatedSprite* get_asprite();  //ZMIANA !
    void hit(int hp);                     //ZMIANA !
    Materia get_materia();          //ZMIANA !
    float getHp() const;


private:
    void move();

    AnimatedSprite sprite;
    const KeyboardSet keyboardSet;
    float raisingForce;
    Direction direction;
    Materia materia;
    bool jumpPressedInLastFrame;
    bool shootPressedInLastFrame;
    float hp;
    int timeOut;
    int naptime;

    static const float fallSpeed;
    static const float walkSpeed;
    static const float jumpForce;
    static const float raisingForceDumping;
    static const float feetWidth;
    static const float weamponPos;
};
