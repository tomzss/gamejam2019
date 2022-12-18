#pragma once

#include "AutoDraw.hpp"
#include "ResourceBank.hpp"

class Animation{
public:
    Animation();
    bool loadFromFile(const sf::String& filename);

    [[nodiscard]] const sf::Texture& getTexture() const;
    [[nodiscard]] uint16_t getFramesCount() const;
    [[nodiscard]] sf::Vector2u getFrameSize() const;
    [[nodiscard]] uint32_t getDefaultFrameTime() const;
    void setDefaultFrameTime(uint32_t defaultFrameTime);

private:
    sf::Texture texture;
    uint16_t framesCount;
    uint32_t frameSize;
    uint32_t defaultFrameTime;
};

class _AnimatedSprite : public sf::Sprite{
public:
    explicit _AnimatedSprite(Animation* animation = nullptr);
    virtual ~_AnimatedSprite();
    const Animation* getAnimation() const;
    void setAnimation(Animation&);
    void update();
    bool isStop() const;
    void setStop(bool stop);

private:
    class Animator : public Actor{
    public:
        explicit Animator(_AnimatedSprite& sprite);
        void update() override;
    private:
        _AnimatedSprite& sprite;
    };

    Animation* animation;
    uint32_t frameTime;
    uint16_t currentFrame;
    uint16_t stepsToNextFrame;
    Animator& animator;
    bool stop;
};

using AnimatedSprite = AutoDraw<_AnimatedSprite>;
using AnimationBank = ResourceBank<Animation>;

