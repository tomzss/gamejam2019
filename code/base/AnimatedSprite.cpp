#include "AnimatedSprite.hpp"
#include <fstream>

bool Animation::loadFromFile(const sf::String& filename){
    std::ifstream stream(filename);
    if(!stream.good()) return false;
    stream.seekg(0, stream.end);
    const unsigned filesize = stream.tellg();
    stream.seekg(0, stream.beg);

    stream.read(reinterpret_cast<char*>(&framesCount), sizeof(framesCount));
    stream.read(reinterpret_cast<char*>(&frameSize), sizeof(frameSize));
    stream.read(reinterpret_cast<char*>(&defaultFrameTime), sizeof(defaultFrameTime));
    const auto textureSize = filesize-(sizeof(framesCount)+sizeof(frameSize)+sizeof(defaultFrameTime));

    auto textureData = std::make_unique<char[]>(textureSize);
    stream.read(textureData.get(), textureSize);
    if(!stream.good()) return false;

    return texture.loadFromMemory(textureData.get(), textureSize);
}

Animation::Animation()
    : framesCount(0)
    , frameSize(0)
    , defaultFrameTime(0)
    {}

uint16_t Animation::getFramesCount() const{
    return framesCount;
}

sf::Vector2u Animation::getFrameSize() const{
    return sf::Vector2u(frameSize, texture.getSize().y);
}

uint32_t Animation::getDefaultFrameTime() const{
    return defaultFrameTime;
}

void Animation::setDefaultFrameTime(uint32_t defaultFrameTime_){
    defaultFrameTime = defaultFrameTime_;
}

const sf::Texture& Animation::getTexture() const{
    return texture;
}

_AnimatedSprite::_AnimatedSprite(Animation* animation)
    : animation(animation)
    , frameTime(0)
    , currentFrame(0)
    , stepsToNextFrame(0)
    , stop(false)
    , animator(Actor::getCurrentCreatingScene().newActor<Animator>(*this))
    {}

void _AnimatedSprite::update(){
    if(stop)
        return;

    if(animation == nullptr)
        return;

    if(stepsToNextFrame == 0){
        stepsToNextFrame = (frameTime==0) ? (animation->getDefaultFrameTime()) : (frameTime);
        auto rect = getTextureRect();
        if(++currentFrame >= animation->getFramesCount()){
            currentFrame = 0;
            rect.left = 0;
        }
        else
            rect.left += animation->getFrameSize().x;
        setTextureRect(rect);
    }
    --stepsToNextFrame;
}

const Animation* _AnimatedSprite::getAnimation() const{
    return animation;
}

void _AnimatedSprite::setAnimation(Animation& animation_){
    currentFrame = 0;
    animation = &animation_;
    setTexture(animation->getTexture());
    sf::Vector2i frameSize(animation->getFrameSize());
    setTextureRect(sf::IntRect(sf::Vector2i(), frameSize));
}

_AnimatedSprite::~_AnimatedSprite(){
    animator.scene.deleteActor(animator);
}

bool _AnimatedSprite::isStop() const{
    return stop;
}

void _AnimatedSprite::setStop(bool stop){
    _AnimatedSprite::stop = stop;
}

_AnimatedSprite::Animator::Animator(_AnimatedSprite& sprite)
    : sprite(sprite){}

void _AnimatedSprite::Animator::update(){
    sprite.update();
}
