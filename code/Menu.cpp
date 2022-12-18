#include "Menu.hpp"
#include "MainGame.hpp"

void setupMainMenu(Scene& scene){
    scene.setName("Menu");
    scene.newActor<Menu>();
}

void Menu::update(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !enterPressedLastFrame)
        setupMainGame(base.newActiveScene());

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !escPressedLastFrame)
        base.forceActor<Window>().close();

    enterPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
    escPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

Menu::Menu()
    : sprite(0)
    , zolw (10)
    , enterPressedLastFrame(false)
    , escPressedLastFrame(false){
    sprite.setTexture(base.forceActor<TextureBank>().get("menustart.png"));
    zolw.setAnimation(base.forceActor<AnimationBank>().get("animacjazolw1.s1a"));
    zolw.setPosition(3200,792);
    zolw.setScale(-1.4,1.4);

    auto& window = base.forceActor<Window>();

    sf::View view;
    view.setSize(sf::Vector2f(sprite.getTexture()->getSize()));

    sf::Vector2f targetSize(sprite.getTexture()->getSize());
    if(targetSize.x > window.getSize().x){
        targetSize.x = window.getSize().x;
        targetSize.y = targetSize.x * window.getSize().y / window.getSize().x;
    }
    if(targetSize.y > window.getSize().y){
        targetSize.x = targetSize.y * window.getSize().x / window.getSize().y;
        targetSize.y= window.getSize().y;
    }

    const sf::Vector2f viewport (
        targetSize.x/window.getSize().x,
        targetSize.y/window.getSize().y
    );

    view.setViewport(sf::FloatRect({0, 0}, viewport));
    view.setCenter(view.getSize()/2.f);
    base.forceActor<Window>().setView(view);
}
