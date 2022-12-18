#include "Player.hpp"
#include "Terrain.hpp"
#include "Bullet.hpp"
#include "Audio.hpp"

const float Player::fallSpeed = 60;
const float Player::walkSpeed = 30;
const float Player::jumpForce = 160;
const float Player::raisingForceDumping = 10;
const float Player::feetWidth = 220;
const float Player::weamponPos = 77;

Player::Player(const sf::Vector2f& position, KeyboardSet keyboardSet, Materia materia)
    : sprite(Layers::player)
    , keyboardSet(keyboardSet)
    , raisingForce(0)
    , direction(Direction::right)
    , materia(materia)
    , jumpPressedInLastFrame(false)
    , shootPressedInLastFrame(false)
    , hp(400)
    , timeOut(0)
    , naptime(0){
    sprite.setPosition(position);
}

void Player::update(){
    move();

    if(timeOut>0)
        return;

    if(sf::Keyboard::isKeyPressed(keyboardSet.shoot) && !shootPressedInLastFrame){
        base.forceActor<Audio>().playShoot();
        sf::Vector2f position;
        if(direction == Direction::right)
            position = sprite.getPosition() + sf::Vector2f(
                sprite.getAnimation()->getFrameSize().x/2,
                weamponPos - sprite.getAnimation()->getFrameSize().y/2
            );
        else if(direction == Direction::left)
            position = sprite.getPosition() + sf::Vector2f(
                -static_cast<int>(sprite.getAnimation()->getFrameSize().x/2),
                weamponPos - sprite.getAnimation()->getFrameSize().y/2
            );
        scene.newActor<Bullet>(position, direction, materia);
    }
    shootPressedInLastFrame = sf::Keyboard::isKeyPressed(keyboardSet.shoot);
}

void Player::move(){
    auto& terrain = scene.forceActor<Terrain>();
    const sf::Vector2f objPos(
        sprite.getPosition().x-sprite.getAnimation()->getFrameSize().x/2,
        sprite.getPosition().y+sprite.getAnimation()->getFrameSize().y/2
    );
    Platform obj(objPos, feetWidth);
    sf::Vector2f movement{};

    float collisionPoint;
    if(terrain.canObjMoveDown(obj, fallSpeed, collisionPoint)){
        movement.y = fallSpeed;
        if(timeOut<=0){
            if(materia == Materia::normal)
                sprite.setAnimation(base.forceActor<AnimationBank>().get("skok1.s1a"));
            else
                sprite.setAnimation(base.forceActor<AnimationBank>().get("skok2.s1a"));
        }
    }else{
        if(timeOut<=0){
            if(sf::Keyboard::isKeyPressed(keyboardSet.right) || sf::Keyboard::isKeyPressed(keyboardSet.left)){
                if(materia == Materia::normal){
                    if(sprite.getAnimation() != &base.forceActor<AnimationBank>().get("gracz1chod.s1a"))
                        sprite.setAnimation(base.forceActor<AnimationBank>().get("gracz1chod.s1a"));
                }else{
                    if(sprite.getAnimation() != &base.forceActor<AnimationBank>().get("gracz2chod.s1a"))
                        sprite.setAnimation(base.forceActor<AnimationBank>().get("gracz2chod.s1a"));
                }
            }else{
                if(materia == Materia::normal)
                    sprite.setAnimation(base.forceActor<AnimationBank>().get("gracz1.s1a"));
                else
                    sprite.setAnimation(base.forceActor<AnimationBank>().get("gracz2.s1a"));
            }
        }
        sprite.setPosition(sprite.getPosition().x, collisionPoint-sprite.getAnimation()->getFrameSize().y/2);
        if(sf::Keyboard::isKeyPressed(keyboardSet.up) && !jumpPressedInLastFrame && timeOut<=0)
            raisingForce = jumpForce;
    }


    movement.y -= raisingForce;
    raisingForce -= raisingForceDumping;
    if(raisingForce<0) raisingForce = 0;

    if(sf::Keyboard::isKeyPressed(keyboardSet.right) && timeOut<=0){
        if(direction == Direction::left)
            sprite.scale(-1, 1);
        direction = Direction::right;
        movement.x = walkSpeed;
    }else if(sf::Keyboard::isKeyPressed(keyboardSet.left) && timeOut<=0){
        if(direction == Direction::right)
            sprite.scale(-1, 1);
        direction = Direction::left;
        movement.x = -walkSpeed;
    }

    sprite.move(movement);

    if(sprite.getPosition().x<0)
        sprite.setPosition(0, sprite.getPosition().y);
    else if(sprite.getPosition().x + sprite.getAnimation()->getFrameSize().x > terrain.getWorldSize().x)
        sprite.setPosition(terrain.getWorldSize().x - sprite.getAnimation()->getFrameSize().x, sprite.getPosition().y);

    if(timeOut>0){
        naptime--;
        if(naptime<=0)
            sprite.setStop(true);
        timeOut--;
        if(timeOut<=0){
            sprite.setStop(false);
            hp = 400;
        }
        return;
    }
    jumpPressedInLastFrame = sf::Keyboard::isKeyPressed(keyboardSet.up);
}

void Player::setAnimation(const sf::String& filename){
    sprite.setAnimation(base.forceActor<AnimationBank>().get(filename));
    sprite.setOrigin(sf::Vector2f(sprite.getAnimation()->getFrameSize()/2u));
}

sf::Vector2f Player::getCenterPosition() const{
    return sprite.getPosition() + sf::Vector2f(sprite.getAnimation()->getFrameSize()/2u);
}

const AnimatedSprite& Player::getSprite() const{
    return sprite;
}

AnimatedSprite* Player::get_asprite()
{
    return &sprite;
}

void Player::hit(int dmg)
{
    if(hp<0)
        return;
    hp-=dmg;
    if(hp<0){
        timeOut = 5*30;
        naptime = 9;
        sprite.setAnimation(base.forceActor<AnimationBank>().get((materia==Materia::normal)?"upadek1.s1a":"upadek2.s1a"));
    }
}

Materia Player::get_materia()
{
    return materia;
}

float Player::getHp() const{
    return hp;
}
