#include "Audio.hpp"

Audio::Audio(){
    bufferSound.loadFromFile("data/szum.wav");
    bufferShoot.loadFromFile("data/boom.wav");
    bufferMusic.loadFromFile("data/uncunc_vincyj.wav");
    sound.setBuffer(bufferSound);
    soundShoot.setBuffer(bufferShoot);
    music.setBuffer(bufferMusic);
    music.setLoop(true);
    music.play();
}

void Audio::playSound(){
    sound.play();
}

void Audio::playShoot(){
    soundShoot.play();
}
