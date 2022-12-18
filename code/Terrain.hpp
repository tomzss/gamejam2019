#pragma once

#include "base/All.hpp"
#include <list>

class Platform{
public:
    Platform(const sf::Vector2f& position, float length);

    [[nodiscard]] const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f& position);
    [[nodiscard]] float getLength() const;
    void setLength(float length);

private:
    sf::Vector2f position;
    float length;
};

class Terrain : public Actor{
public:
    Terrain(const sf::Vector2f& worldSize);
    bool canObjMoveDown(const Platform& obj, float distance, float& endPos);
    const sf::Vector2f& getWorldSize() const;
    void newPlatform(const sf::Vector2f& position, float length);

private:
    std::vector<Platform> platforms;
    sf::Vector2f worldSize;

    static bool canObjMoveDown(const Platform& obj, float distance, const Platform& platform, float& endPos);
};


