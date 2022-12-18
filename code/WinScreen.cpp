#include "WinScreen.hpp"
#include "Terrain.hpp"

void setupWinScreen(Scene& scene, Materia materia){
    scene.newActor<WinScreen>(materia);
}

void WinScreen::update(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !escPressedLastFrame){
        auto* menu = base.findScene("Menu");
        assert(menu);
        base.deleteScene(scene);
        base.setActiveScene(*menu);
        return;
    }

    escPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

WinScreen::WinScreen(Materia materia)
    : sprite(1)
    , dance(2){
    auto& window = base.forceActor<Window>();
    if(materia == Materia::normal){
        sprite.setTexture(base.forceActor<TextureBank>().get("ekranzwyciestwo1.png"));
        dance.setAnimation(base.forceActor<AnimationBank>().get("animacjazwyciestwo1.s1a"));
    }else{
        sprite.setTexture(base.forceActor<TextureBank>().get("ekranzwyciestwo2.png"));
        dance.setAnimation(base.forceActor<AnimationBank>().get("animacjazwyciestwo2.s1a"));
    }
    scene.newActor<Terrain>(sf::Vector2f(sprite.getTexture()->getSize()));
    dance.setPosition(sf::Vector2f(sprite.getTexture()->getSize()/2u));
    for(auto i=0; i<20; ++i){
        auto& animal = animals.emplace_back(&scene.newActor<FlyingAnimal>(sf::Vector2f(
            std::rand() % sprite.getTexture()->getSize().x,
            std::rand() % sprite.getTexture()->getSize().y
        )));
        animal->setAnimation((materia==Materia::normal)?((rand()%2)?"animacjamotyl1.s1a":"animacjaryba1.s1a"):((rand()%2)?"animacjamotyl2.s1a":"animacjaryba2.s1a")); // #czystykod
        animal->scale(1.3);
    }
}

WinScreen::~WinScreen(){
    for(auto& i: animals)
        scene.deleteActor(*i);
}
