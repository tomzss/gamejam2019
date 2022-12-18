#include "Menu.hpp"
#include "Audio.hpp"

int main(){
    std::srand(std::time(nullptr));
    ResourcePrefix = "data/";

    auto& window = base.newActor<Window>(sf::VideoMode::getDesktopMode(), "Test");
    window.setFramerateLimit(30); // 30 FPS

    base.newActor<Audio>();

    setupMainMenu(base.newActiveScene());

    while(window.isOpen())
        base.updateBase();
}
