#pragma once

#include "base/All.hpp"
#include "Animal.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Kabum.h"

class GameManager : public Actor{
public:
    GameManager(const sf::Vector2f& minimalSize, const sf::Vector2f& maximalSize);
    void update() override;

private:
    void hpBars();
    void spawn();
    void animal_figth(std::vector<Animal*>&  wektor);
    void bullet_figth(std::vector<Bullet*>&  kule);
    float get_odl(sf::Vector2f x,sf::Vector2f y);
    void shut_to_animal(std::vector<Bullet*>&  kule,std::vector<Animal*>&  motyle,
                        std::vector<Animal*>&  ryby,std::vector<Animal*>&  zolwie);
    void shut_to_specie(std::vector<Bullet*>&  kule,std::vector<Animal*>&  gatunek);
    void shut_to_People(std::vector<Bullet*>&  kule,std::vector<Player*>&  People);
    void kabum_hit     (std::vector<Kabum*>&  kabum,std::vector<Player*>&  People);
  //  bool is_in_sprite(sf::Sprite & sprite,sf::Vector2f bullet_pos);
    float odl_min_animal;
    float odl_min_kul;
    sf::Vector2f minimalSize;
    sf::Vector2f maximalSize;
    sf::View view;
    Sprite background;
    RectangleShape hpBar1;
    RectangleShape hpBar2;
    unsigned framesToNextSpawn;
    int hp_bullet;
    int hp_kabum;
};
