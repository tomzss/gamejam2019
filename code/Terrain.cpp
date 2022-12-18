#include "Terrain.hpp"

Platform::Platform(const sf::Vector2f& position, float length)
    : position(position)
    , length(length){}

const sf::Vector2f& Platform::getPosition() const{
    return position;
}

void Platform::setPosition(const sf::Vector2f& position_){
    position = position_;
}

float Platform::getLength() const{
    return length;
}

void Platform::setLength(float length_){
    length = length_;
}

Terrain::Terrain(const sf::Vector2f& worldSize)
    : worldSize(worldSize){}

bool Terrain::canObjMoveDown(const Platform& obj, float distance, float& endPos){
    if(obj.getPosition().y+distance > worldSize.y){
        endPos = worldSize.y;
        return false;
    }

    for(auto& platform : platforms){
        if(!canObjMoveDown(obj, distance, platform, endPos))
            return false;
    }
    return true;
}

bool Terrain::canObjMoveDown(const Platform& obj, float distance, const Platform& platform, float& endPos){
    // idzie w górę
    if(distance < 0)
        return true;

    // rozminą się w pionie
    if(obj.getPosition().y > platform.getPosition().y
       || obj.getPosition().y+distance < platform.getPosition().y)
        return true;

    // rozminą się w poziomie
    if(obj.getPosition().x > platform.getPosition().x+platform.getLength()
       || obj.getPosition().x+obj.getLength() < platform.getPosition().x)
        return true;

    // jak nie powyższe to kolizja
    endPos = platform.getPosition().y;
    return false;
}

const sf::Vector2f& Terrain::getWorldSize() const{
    return worldSize;
}

void Terrain::newPlatform(const sf::Vector2f& position, float length){
    platforms.emplace_back(position, length);
}
