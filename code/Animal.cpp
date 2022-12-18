#include "Animal.hpp"
#include "Enums.hpp"
#include "Terrain.hpp"
#include <math.h>
#include <iostream>
const float Animal::marginToTarget = 10;
const float Animal::speed = 4;

Animal::Animal(const sf::Vector2f& position)
    : sprite(Layers::animal){
    sprite.setPosition(position);
}
void Animal::setAnimation(const sf::String& filename) {
    if(filename.find('2')== std::string::npos)
    {
        materia = Materia::normal;
    }else
    {
        materia = Materia::anty;
    }
    if(filename.find("ryba") != std::string::npos)
    {
        animal_t = Animal_type::ryba;
    }else if(filename.find("zolw") != std::string::npos)
    {
        animal_t = Animal_type::zolw;
    }else if(filename.find("motyl") != std::string::npos)
    {
        animal_t = Animal_type::motyl;
    }
    sprite.setAnimation(base.forceActor<AnimationBank>().get(filename));
}

Animal_type Animal::get_A_type()
{
    return animal_t;
}
sf::Vector2f Animal::getPosition()
{
    return sprite.getPosition();
}
Materia Animal::get_material()
{
    return  materia;
}


void Animal::scale(float x){
    sprite.scale(x, x);
}

FlyingAnimal::FlyingAnimal(const sf::Vector2f& position):
    Animal(position)
{
    first_time = true;

}


void FlyingAnimal::update(){
    if(first_time)
    {
        randTarget();
        sf::Vector2f srodek;
        srodek.x = ((sprite.getAnimation()->getFrameSize().x)*sprite.getScale().x)/2;
        sprite.setOrigin(srodek);

    }
    bool gotTarget = true;

    if(std::abs(sprite.getPosition().x-target.x) > marginToTarget)
        gotTarget = false;
    if(std::abs(sprite.getPosition().y-target.y) > marginToTarget)
        gotTarget = false;

    if(gotTarget || first_time)
    {
        randTarget();
        float odl = sqrt(pow((target.x-sprite.getPosition().x),2)+pow((target.y-sprite.getPosition().y),2));
        direction.x = (target.x-sprite.getPosition().x)/odl;
        direction.y = (target.y-sprite.getPosition().y)/odl;
        if((target.x-sprite.getPosition().x)<0)
        {
            sf::Vector2f new_Scale =sprite.getScale();
            new_Scale.x  = -std::abs(new_Scale.x);
            sprite.setScale(new_Scale);
        } else
        {
            sf::Vector2f new_Scale =sprite.getScale();
            new_Scale.x  = std::abs(new_Scale.x);
            sprite.setScale(new_Scale);

        }
        //std::cout<<"odl : "<<odl<<std::endl;
    }
    //std::cout<<direction.x<<" "<<direction.y<<std::endl;
    sprite.move((direction)*speed);
    first_time = false;
}

void FlyingAnimal::randTarget(){
    const auto worldSize = scene.forceActor<Terrain>().getWorldSize();
    const auto spawnArea = sf::Vector2u(worldSize) - sprite.getAnimation()->getFrameSize();

    target.x = std::rand() % static_cast<int>(spawnArea.x-(sprite.getAnimation()->getFrameSize().x));
    target.y = std::rand() % static_cast<int>(spawnArea.y-(sprite.getAnimation()->getFrameSize().y));

    target.x += (sprite.getAnimation()->getFrameSize().x)/2;
    target.y += (sprite.getAnimation()->getFrameSize().y)/2;

 }




WalkingAnimal::WalkingAnimal(const sf::Vector2f& position,const float way):
        Animal(position)
{
    pos = position;
    road = way;//droga jest liczona na prawo od pozycji pierwotnej
    first_time = true;

}


void WalkingAnimal::update(){
    if(first_time)
    {
        sf::Vector2f orgin ;
        orgin.x= static_cast<float >(sprite.getAnimation()->getFrameSize().x/2);
        orgin.y= static_cast<float >(sprite.getAnimation()->getFrameSize().y);
        sprite.setOrigin(orgin);
        road = road - sprite.getAnimation()->getFrameSize().x;
        randTarget();
        /*
        sf::Vector2f srodek;
        srodek.x = (sprite.getAnimation()->getFrameSize().x*sprite.getScale().x)/2;
        sprite.setOrigin(srodek);
         */

    }
    bool gotTarget = true;

    if(std::abs(sprite.getPosition().x-target) > marginToTarget)
        gotTarget = false;

    if(gotTarget || first_time)
    {
        randTarget();
        if((target-sprite.getPosition().x)<0)
        {
            sf::Vector2f new_Scale =sprite.getScale();
            new_Scale.x  = -std::abs(new_Scale.x);
            sprite.setScale(new_Scale);
        } else
        {
            sf::Vector2f new_Scale =sprite.getScale();
            new_Scale.x  = std::abs(new_Scale.x);
            sprite.setScale(new_Scale);
        }
        //std::cout<<"odl : "<<odl<<std::endl;
    }
    //std::cout<<direction.x<<" "<<direction.y<<std::endl;
    float speed_l;
    if(target-sprite.getPosition().x > 0)
    {
        speed_l = speed;
    }else
    {
        speed_l = speed*(-1);
    }
    sprite.move(sf::Vector2f(speed_l,0));
    first_time = false;
}

void WalkingAnimal::randTarget(){
    //   const auto worldSize = scene.forceActor<Terrain>().getWorldSize();
    //   const auto spawnArea = sf::Vector2u(worldSize) - sprite.getTexture()->getSize();

    target =pos.x + std::rand() % static_cast<int>(road) ;
}

AnimatedSprite *Animal::get_asprite()
{
    return &sprite;
}
void Animal::set_matirial(Materia materia_new)
{
    materia = materia_new;
    std::string plik;
    std::string typ;
    switch(animal_t)
    {
        case Animal_type::zolw:
            typ = "zolw";
            break;
        case Animal_type ::ryba:
            typ="ryba";
            break;
        case Animal_type ::motyl:
            typ="motyl";
            break;
        default:
            std::cout<<"Przypal";
    }
    std::string nr;
    switch(materia)
    {
        case Materia::normal :
            nr ="1";
            break;
        case Materia::anty :
            nr ="2";
            break;
        default:
            std::cout<<"Przypal z materia";
    }
    plik = "animacja"+typ+nr+".s1a";
    //std::cout<<plik<<std::endl;
    sprite.setAnimation(base.forceActor<AnimationBank>().get(plik));
}
