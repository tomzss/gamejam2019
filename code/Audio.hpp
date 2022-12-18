#pragma once

#include "base/All.hpp"
#include <SFML/Audio.hpp>

class Audio : public Actor{
public:
    Audio();

    void playSound();
    void playShoot();

private:
    sf::SoundBuffer bufferSound;
    sf::SoundBuffer bufferShoot;
    sf::SoundBuffer bufferMusic;
    sf::Sound sound;
    sf::Sound soundShoot;
    sf::Sound music;
};


