#pragma once

#include "Scene.hpp"

class Base : public Scene{
public:
    /// Tworzy pustą scenę o podanym imieniu.
    Scene& newScene(const std::string& name = "");

    /// Tworzy pustą scenę o podanym imieniu i ustawia ją jako aktywną.
    Scene& newActiveScene(const std::string&  name= "");

    /// Ustawia scenę jako aktywną.
    void setActiveScene(Scene&);

    /// Zwraca aktywną scenę.
    Scene* getActiveScene();

    /// Usuwa podaną scenę.
    void deleteScene(Scene&);

    /// Zwraca scenę o podanym imieniu. Jeśli takiej nie ma zwraca nullptr.
    Scene* findScene(const std::string& name);

    /// Zwraca wektor wskaźników na sceny.
    [[nodiscard]] const std::vector<std::unique_ptr<Scene>>& getScenes() const;

    /// Wywołuje metodę update dla siebie i aktywnej sceny.
    void updateBase();


    // ==================================================
    Base() noexcept;
    ~Base();

private:
    std::vector<std::unique_ptr<Scene>> scenes;
    Scene* activeScene;
} inline base;

