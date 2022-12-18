
#include "GameManager.hpp"
#include "Player.hpp"
#include "Terrain.hpp"
#include "Animal.hpp"
#include "Enums.hpp"
#include "Bullet.hpp"
#include "Kabum.h"
#include "WinScreen.hpp"
#include <cmath>


GameManager::GameManager(const sf::Vector2f& minimalSize, const sf::Vector2f& maximalSize)
    : background(Layers::background)
    , minimalSize(minimalSize)
    , maximalSize(maximalSize)
    , hpBar1(10)
    , hpBar2(10)
    , hp_bullet(50)
    , hp_kabum(5)
    , odl_min_kul(10)
    , odl_min_animal(80)
    , framesToNextSpawn(1)
    {
    hpBar1.setFillColor(sf::Color::Magenta);
    hpBar2.setFillColor(sf::Color::Cyan);

    const auto& window = base.forceActor<Window>();
    const auto& terrain = scene.forceActor<Terrain>();

    background.setTexture(base.forceActor<TextureBank>().get("plansza.png"));
    background.scale(
        terrain.getWorldSize().x/background.getTexture()->getSize().x,
        terrain.getWorldSize().y/background.getTexture()->getSize().y
    );

    for(auto i=0; i<15; i++){
        framesToNextSpawn=1;
        spawn();
    }
}

void GameManager::update(){
    auto players = scene.getAllTyped<Player>();
    auto zolwie = scene.getAllTyped<Animal>(Animal_type::zolw);
    auto motyle = scene.getAllTyped<Animal>(Animal_type::motyl);
    auto ryby = scene.getAllTyped<Animal>(Animal_type::ryba);
    auto pociski = scene.getAllTyped<Bullet>();
    auto kabum = scene.getAllTyped<Kabum>();

// Animale są wykorzystane poniżej
    //Zderzenia wzajemne zwierząt
    animal_figth(ryby);
    animal_figth(zolwie);
    animal_figth(motyle);

    // Strzelanie do bezbronnych zwierzątek :(
    shut_to_animal(pociski,motyle,ryby,zolwie);

    //Strzelanie do ludzi :)
    shut_to_People(pociski,players);

    //Obrażenia od wybuchu
    kabum_hit(kabum,players);

    //Dezintegracja kul
    bullet_figth(pociski);

    spawn();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        setupWinScreen(base.newActiveScene(), Materia::normal );

    unsigned materia = 0;
    unsigned antymateria = 0;

    for(auto& i: zolwie){
        if(i->get_material() == Materia::normal) materia++;
        else antymateria++;
    }
    for(auto& i: motyle){
        if(i->get_material() == Materia::normal) materia++;
        else antymateria++;
    }
    for(auto& i: ryby){
        if(i->get_material() == Materia::normal) materia++;
        else antymateria++;
    }

    if(materia/static_cast<float>(antymateria) >= 7/1.f)
        setupWinScreen(base.newActiveScene(), Materia::normal);
    if(materia/static_cast<float>(antymateria) <= 1/7.f)
        setupWinScreen(base.newActiveScene(), Materia::anty);

}

void GameManager::spawn(){
    if(scene.getAllTyped<Animal>().size()>50)
        return;
    --framesToNextSpawn;
    if(framesToNextSpawn == 0){
        framesToNextSpawn = 30;
        auto& terrain = scene.forceActor<Terrain>();
        sf::Vector2f position;
        const float margin = 300;
        switch(rand()%4){ // where?
        case 0: position = sf::Vector2f(-margin, rand() % static_cast<int>(terrain.getWorldSize().y)); break;
        case 1: position = sf::Vector2f(terrain.getWorldSize().x+margin, static_cast<int>(terrain.getWorldSize().y)); break;
        case 2: position = sf::Vector2f(rand() % static_cast<int>(terrain.getWorldSize().y), -margin); break;
        case 3: position = sf::Vector2f(static_cast<int>(terrain.getWorldSize().y), terrain.getWorldSize().x+margin); break;
        }
        int materia = (rand()%2)+1;
        Animal* animal;
        switch(rand()%2){ // what?
        case 0: animal = &scene.newActor<FlyingAnimal>(position); animal->setAnimation("animacjaryba" +std::to_string(materia)+".s1a"); break;
        case 1: animal = &scene.newActor<FlyingAnimal>(position); animal->setAnimation("animacjamotyl"+std::to_string(materia)+".s1a"); break;
        }
    }
    // tak, wiem, że to z złe zło
    static bool p_obrot = true;
    if(p_obrot) {
        {
            auto &animal1 = scene.newActor<WalkingAnimal>(sf::Vector2f(2010, 1032), 495);
            animal1.setAnimation("animacjazolw2.s1a");
        }
        {
            auto &animal1 = scene.newActor<WalkingAnimal>(sf::Vector2f(3180, 1180), 531);
            animal1.setAnimation("animacjazolw2.s1a");
        }
        {
            auto &animal1 = scene.newActor<WalkingAnimal>(sf::Vector2f(2467, 1634), 532);
            animal1.setAnimation("animacjazolw1.s1a");
        }
        {
            auto &animal1 = scene.newActor<WalkingAnimal>(sf::Vector2f(411, 1268), 931);
            animal1.setAnimation("animacjazolw2.s1a");
        }

        {
            auto &animal1 = scene.newActor<WalkingAnimal>(sf::Vector2f(2666, 2169), 1053);
            animal1.setAnimation("animacjazolw1.s1a");
        }

        {
            auto &animal1 = scene.newActor<WalkingAnimal>(sf::Vector2f(1783, 2140), 532);
            animal1.setAnimation("animacjazolw2.s1a");
        }
        {
            auto &animal1 = scene.newActor<WalkingAnimal>(sf::Vector2f(1953, 2619), 714);
            animal1.setAnimation("animacjazolw1.s1a");
        }
        {
            auto &animal1 = scene.newActor<WalkingAnimal>(sf::Vector2f(0, 1952), 1379);
            animal1.setAnimation("animacjazolw1.s1a");
        }
        {
            auto &animal1 = scene.newActor<WalkingAnimal>(sf::Vector2f(0, 2660), 1052);
            animal1.setAnimation("animacjazolw1.s1a");
        }
        p_obrot = false;
    }
}

float GameManager::get_odl(sf::Vector2f a, sf::Vector2f b)
{
    return sqrt(pow(a.x-b.x,2)+pow((a.y-b.y),2));

}

void GameManager::animal_figth(std::vector<Animal *> &wektor)
{
    std::vector<int> tab;
    for(int i=0;i<wektor.size();i++)
    {
        for(int j=(i+1);j<wektor.size();j++)
        {
            if((get_odl(wektor[i]->getPosition(),wektor[j]->getPosition()))<odl_min_animal)
            {
                bool integracja = false;
                if(wektor[i]->get_material() != wektor[j]->get_material())
                    integracja = true;
                if(integracja)
                {
                    scene.newActor<Kabum>(wektor[i]->getPosition(),1.5,hp_kabum);
                    tab.push_back(i);
                    tab.push_back(j);
                }
            }
        }
    }
    if(tab.size()>0)
    {
        int zr = 0;
        sort(tab.begin(),tab.end());
        for(int i=0;i<tab.size();i++)
        {
            if(tab[i]!= zr)
            {
                scene.deleteActor(*wektor[tab[i]]);
            }
        }
    }
}

void GameManager::shut_to_animal(std::vector<Bullet *> &kule, std::vector<Animal *> &motyle,
                                 std::vector<Animal *> &ryby, std::vector<Animal *> &zolwie)
    {
        shut_to_specie(kule,motyle);
        shut_to_specie(kule,ryby);
        shut_to_specie(kule,zolwie);
    }
void GameManager::shut_to_specie(std::vector<Bullet *> &kule, std::vector<Animal *> &gatunek)
{

    for(int i=0;i<kule.size();i++) {
        for (int j = (0); j < gatunek.size(); j++)
        {
            if (gatunek[j]->get_asprite()->getGlobalBounds().contains(kule[i]->get_Position())) {
                if (gatunek[j]->get_material() != kule[i]->getMateria())
                {
                    gatunek[j]->set_matirial(kule[i]->getMateria());
                    scene.deleteActor(*kule[i]);
                    break;
                }
            }
        }
    }
}
void GameManager::shut_to_People(std::vector<Bullet *> &kule, std::vector<Player *> &People)
{
    for(int k_i=0;k_i<kule.size();k_i++)
    {
        for(int p_j=0;p_j<People.size();p_j++)
        {
            if(People[p_j]->get_asprite()->getGlobalBounds().contains(kule[k_i]->get_Position()))
            {
                if(People[p_j]->get_materia() != kule[k_i]->getMateria())
                {
                    People[p_j]->hit(hp_bullet);
                    scene.newActor<Kabum>(kule[k_i]->get_Position(),1,0);
                    scene.deleteActor(*kule[k_i]);
                    break;
                }
            }

        }
    }
}
void GameManager::kabum_hit(std::vector<Kabum *> &kabum, std::vector<Player *> &People)
{
    for(int k_i=0;k_i<kabum.size();k_i++)
    {
        for(int p_j=0;p_j<People.size();p_j++)
        {
            {
                if(People[p_j]->get_asprite()->getGlobalBounds().intersects(kabum[k_i]->get_asprite()->getGlobalBounds()))
                {
                    People[p_j]->hit(hp_kabum);
                }
            }

        }
    }
}

void GameManager::bullet_figth(std::vector<Bullet *> &kule)
{
    std::vector<int> tab;
    for(int i=0;i<kule.size();i++)
    {
        for(int j=(i+1);j<kule.size();j++)
        {
            if((get_odl(kule[i]->get_Position(),kule[j]->get_Position()))<odl_min_kul)
            {
                bool anichilacja = false;
                if(kule[i]->getMateria() != kule[j]->getMateria())
                    anichilacja = true;
                if(anichilacja)
                {
                    scene.newActor<Kabum>(kule[i]->get_Position(),0.5,hp_kabum);
                    tab.push_back(i);
                    tab.push_back(j);
                }
            }
        }
    }
    if(tab.size()>0)
    {
        int zr = 0;
        sort(tab.begin(),tab.end());
        for(int i=0;i<tab.size();i++)
        {
            if(tab[i]!= zr)
            {
                scene.deleteActor(*kule[tab[i]]);
            }
        }
    }
}

void GameManager::hpBars(){
    auto& terrain = base.forceActor<Terrain>();
    auto players = scene.getAllTyped<Player>();
    assert(players.size()==2);
    float proportion = players[1]->getHp()/players[0]->getHp();
    hpBar1.setSize(sf::Vector2f(terrain.getWorldSize().x/2*proportion, 1000));
    hpBar2.setPosition(hpBar2.getSize().x, 0);
    hpBar2.setSize(sf::Vector2f(terrain.getWorldSize().x-hpBar1.getSize().x, 1000));
}
