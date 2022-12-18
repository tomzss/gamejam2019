#pragma once

#include <cassert>
#include <vector>
#include <memory>

class Scene;

class Actor{
public:
    /// Do nadpisania w klasie dziedziczącej, wywoływane przez scenę co klatkę.
    virtual void update(){}

    /// Scena do której należy aktor.
    Scene& scene;


    //==================================================
    Actor();
    virtual ~Actor() = default;

    template<typename T, typename...Args> static std::unique_ptr<T> makeUnique(Scene& parent, Args&&...);

    static Scene& getCurrentCreatingScene();
private:
    static inline std::vector<Scene*> creatingScenes;
};

template<typename T, typename... Args>
std::unique_ptr<T> Actor::makeUnique(Scene& parent, Args&&...args){
    static_assert(std::is_base_of_v<Actor, T>);
    creatingScenes.emplace_back(&parent);
    auto newActorPtr = std::make_unique<T>(std::forward<Args>(args)...);
    creatingScenes.pop_back();
    return std::move(newActorPtr);
}


