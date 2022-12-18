#pragma once

#include <SFML/Graphics/Font.hpp>
#include "Actor.hpp"

inline sf::String ResourcePrefix;

/// Klasa do wygodniejszego wczytywania tekstur i czcionek (odpowiednio jako TextureBank FontBank)
/// T oznacza sf::Texture / sf::Font
template <typename T>
class ResourceBank : public Actor{
public:
    /// Zwraca referencję na obiekt wczytany z podanej ścieżki (jak trzeba to wczytuje).
    [[nodiscard]] T& get(const sf::String& filename);

    /// Czy obiekt z podanej ścieżki został wczytany?
    [[nodiscard]] bool haveLoaded(const sf::String& filename) const;

    /// Kasuje dany obiekt.
     void unload(const T& resource) const;

    /// Kasuje obiekt wczytany spod podanej ścieżki.
     void unload(const sf::String& filename) const;

    /// Wymusza ponowne wczytanie obiektu i go zwraca.
    T& reload(const T& resource) const;

    /// Wymusza ponowne wczytanie obiektu spod podanej ścieżki i go zwraca. Jeśli nie był wczytany to po prostu wczytuje.
    T& reload(const sf::String& filename) const;

    /// Zwraca nazwę pliku z którego wczytano dany obiekt. Jeśli nie wczytano takiego obiekt zwraca "".
    [[nodiscard]] sf::String nameOf(const T& resource) const;

private:
    std::map<sf::String, T> resources;
};

using TextureBank = ResourceBank<sf::Texture>;
using FontBank = ResourceBank<sf::Font>;



// ==================================================

template<typename T>
T& ResourceBank<T>::get(const sf::String& filename){
    auto iter = resources.find(ResourcePrefix+filename);
    if(iter == resources.end()){
        // auto& newResource = resources.emplace().first->second;
        auto& newResource = resources[ResourcePrefix+filename];
        newResource.loadFromFile(ResourcePrefix+filename);
        return newResource;
    }
    return iter->second;
}

template<typename T>
bool ResourceBank<T>::haveLoaded(const sf::String& filename) const{
    return resources.find(ResourcePrefix+filename) != resources.end();
}

template<typename T>
void ResourceBank<T>::unload(const T& resource) const{
    auto& iter = find_if(resources.begin(), resources.end(), [&resource](auto& i){ return &(i.second)==&resource; });
    if( iter != resources.end())
        resources.erase(iter);
}

template<typename T>
void ResourceBank<T>::unload(const sf::String& filename) const{
    auto& iter = resources.find(ResourcePrefix+filename);
    if( iter != resources.end())
        resources.erase(iter);
}

template<typename T>
T& ResourceBank<T>::reload(const T& resource) const{
    auto& iter = find_if(resources.begin(), resources.end(), [&resource](auto& i){ return &(i.second)==&resource; });
    if( iter != resources.end())
        resource.loadFromFile(iter->first);
    return resource;
}

template<typename T>
T& ResourceBank<T>::reload(const sf::String& filename) const{
    auto& resource = resources[ResourcePrefix+filename];
    resource.loadFromFile(ResourcePrefix+filename);
    return resource;
}

template<typename T>
sf::String ResourceBank<T>::nameOf(const T& resource) const{ // TODO
    assert(false);
}



