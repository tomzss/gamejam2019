#pragma once

#include <algorithm>
#include "Actor.hpp"
#include "../Enums.hpp"

class Scene{
public:
    /// Imię służy do znajdywania sceny w bazie. (patrz: Base::findScene)
    explicit Scene(const std::string& name = "");
    [[nodiscard]] const std::string& getName() const;
    void setName(const std::string& name);

    /// Tworzy aktora i zwraca na niego referencję.
    template <typename ActorType, typename...Args> ActorType& newActor(Args&&...);

    /// Zwraca przypadkowego aktora danego typu. Jeśli takiego nie ma to go tworzy z podanymi argumentami.
    template <typename ActorType, typename...Args> ActorType& forceActor(Args&&...);

    /// Zwraca wektor wskaźników na wszystkich aktorów danego typu z danej sceny.
    template <typename ActorType> std::vector<ActorType*> getAllTyped();
    //Wersja dla Animali
    template <typename ActorType> std::vector<ActorType*> getAllTyped(Animal_type type);

    /// Kasuje aktora.
    /// Od tego momentu wszystkie wskaźniki/referencje na tego aktora są wadliwe!
    /// Jeśli aktor popełnia samobójstwo deleteActor(*this) nie może już odwoływać się do swoich składowych.
    void deleteActor(Actor&);
    /// Zwraca wektor wskaźników na aktorów.
    [[nodiscard]] const std::vector<std::unique_ptr<Actor>>& getActors() const;

    /// Wywołuje u wszystkich aktorów metodę update.
    void update();

    //==================================================

    void condemnToDeath(); // don't ask...

private:
    std::string name;
    std::vector<std::unique_ptr<Actor>> actors;
    bool shouldIDie;
    std::size_t i; // do iterowania po aktorach
};


template<typename T, typename...Args>
T& Scene::newActor(Args&&...args){
    static_assert(std::is_base_of_v<Actor, T>);
    --i;
    auto actorPtr = Actor::makeUnique<T>(*this, std::forward<Args>(args)...);
    auto& actor = *actorPtr;
    assert(actorPtr != nullptr);
    actors.emplace_back(std::move(actorPtr));
    assert(std::find(actors.begin(), actors.end(), nullptr) == actors.end());
    return actor;
}

template<typename ActorType, typename...Args>
ActorType& Scene::forceActor(Args&&...args){
    for(auto& ptr: actors){
        assert(ptr != nullptr);
        if(auto typedPtr = dynamic_cast<ActorType*>(ptr.get()))
            return *typedPtr;
    }
    if constexpr(std::is_constructible_v<ActorType, Args...>)
       return newActor<ActorType>(std::forward<Args>(args)...);
    else
        assert(false);
}

template<typename ActorType>
std::vector<ActorType*> Scene::getAllTyped(){
    static_assert(std::is_base_of_v<Actor, ActorType>);
    std::vector<ActorType*> out;
    for(auto& actor: actors)
        if(auto* typed=dynamic_cast<ActorType*>(actor.get()); typed)
            out.emplace_back(typed);
    return std::move(out);
}
template<typename ActorType>
std::vector<ActorType*> Scene::getAllTyped(Animal_type type){
    static_assert(std::is_base_of_v<Actor, ActorType>);
    std::vector<ActorType*> out;
    for(auto& actor: actors)
        if(auto* typed=dynamic_cast<ActorType*>(actor.get()); typed)
        {
            if(typed->get_A_type() == type )
                out.emplace_back(typed);
        }

    return std::move(out);
}

