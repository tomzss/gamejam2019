#include "MainGame.hpp"
#include "Terrain.hpp"
#include "Player.hpp"
#include "Animal.hpp"
#include "GameManager.hpp"

void setupTerrain(Scene& scene);

void setupPlayers(Scene& scene){
    const float distanceBetweenPlayers = 500; // TODO
    const sf::Vector2f mainPosition(scene.forceActor<Terrain>().getWorldSize().x/2, scene.forceActor<Terrain>().getWorldSize().y-500); // TODO

    // normal player
    {
        KeyboardSet ks{
            sf::Keyboard::Left,
            sf::Keyboard::Right,
            sf::Keyboard::Up,
            sf::Keyboard::Down,
            sf::Keyboard::Return
        };
        sf::Vector2f position = mainPosition;
        position.x += distanceBetweenPlayers/2.f;
        auto& player = scene.newActor<Player>(position, ks, Materia::normal);
        player.setAnimation("gracz1.s1a");
    }

    // anty player
    {
        KeyboardSet ks{
            sf::Keyboard::A,
            sf::Keyboard::D,
            sf::Keyboard::W,
            sf::Keyboard::S,
            sf::Keyboard::LControl
        };
        sf::Vector2f position = mainPosition;
        position.x -= distanceBetweenPlayers/2.f;
        auto& player = scene.newActor<Player>(position, ks, Materia::anty);
        player.setAnimation("gracz2.s1a");
    }
}

void setupTerrain(Scene& scene){
    auto& terrain = scene.newActor<Terrain>(sf::Vector2f(base.forceActor<TextureBank>().get("plansza.png").getSize()));
    terrain.newPlatform(sf::Vector2f(1910, 1032), 495);
    terrain.newPlatform(sf::Vector2f(3080, 1180), 531);
    terrain.newPlatform(sf::Vector2f(2367, 1634), 532);
    terrain.newPlatform(sf::Vector2f(1910, 1035), 496);
    terrain.newPlatform(sf::Vector2f(411, 1268), 931);
    terrain.newPlatform(sf::Vector2f(2666, 2169), 1053);
    terrain.newPlatform(sf::Vector2f(1783, 2140), 532);
    terrain.newPlatform(sf::Vector2f(1953, 2619), 714);
    terrain.newPlatform(sf::Vector2f(0, 1952), 1379);
    terrain.newPlatform(sf::Vector2f(0, 2660), 1052);
    terrain.newPlatform(sf::Vector2f(0, 2953), 3721);
}

void setupMainGame(Scene& scene){
    setupTerrain(scene);
    setupPlayers(scene);

    scene.newActor<GameManager>(sf::Vector2f(1000, 1000), sf::Vector2f(base.forceActor<TextureBank>().get("plansza.png").getSize()));
}
