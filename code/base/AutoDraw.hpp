#pragma once

#include <SFML/Graphics.hpp>
#include "Base.hpp"

/// Okno SFML-a będące aktorem, pamiętające, co ma rysować i zamykające się na X.
class Window : public Actor, public sf::RenderWindow{
public:
    /// Można tworzyć z takimi samymi argumentami, jak sf::renderWindow.
    template <typename...Args> explicit Window(Args&&...);

    /// W przeciwieństwie do sf::RenderWindow można tworzyć bez argumentów: tworzy okno o nazwie "sbngj" na fullscreen, 30fps.
    Window();


    //==================================================

    /// Zapisuje obiekt do wyrysowania w następnej klatce.
    void drawMe(const sf::Drawable&, int layer);
    void dontDrawMe(const sf::Drawable&);

    void update() override;

private:
    std::vector<std::pair<const sf::Drawable*, int>> drawables;
};

class Drawer : public Actor{
public:
    Drawer(Window&, const sf::Drawable&, int layer);
    void update() override;

    [[nodiscard]] int getLayer() const;
    void setLayer(int layer);

    [[nodiscard]] Window& getWindow() const;
    virtual ~Drawer();
private:
    const sf::Drawable& drawable;
    Window& window;
    int layer;
};


/// Obiekt do wyrysowania w podanym w konstruktorze oknie. Jeśli okno nie jest podane tworzy sobie domyślne okno w bazie.
template <typename T>
class AutoDraw : public T{
public:
    /// Obiekt będzie rysowany w podanym oknie na podanej warstwie.
    AutoDraw(Window&, int layer);

    /// Obiekt będzie rysowany w oknie bezpośrednio w bazie. Na podanej warstwie.
    explicit AutoDraw(int layer);

    /// Okno, w którym obiekt jest rysowany.
    [[nodiscard]] Window& getWindow() const;

    [[nodiscard]] int getLayer() const;
    void setLayer(int layer);

    // ==================================================
    ~AutoDraw();

private:
    Drawer& drawer;
};

using Text = AutoDraw<sf::Text>;
using Sprite = AutoDraw<sf::Sprite>;
using RectangleShape = AutoDraw<sf::RectangleShape>;
using CircleShape = AutoDraw<sf::CircleShape>;
using VertexArray = AutoDraw<sf::VertexArray>;
using ConvexShape = AutoDraw<sf::ConvexShape>;

template<typename... Args>
Window::Window(Args&& ... args)
    : sf::RenderWindow(std::forward<Args>(args)...){}

template<typename T>
AutoDraw<T>::AutoDraw(Window& window, int layer)
    : drawer(Actor::getCurrentCreatingScene().newActor<Drawer>(window, *this, layer)){}

template<typename T>
AutoDraw<T>::AutoDraw(int layer)
    : AutoDraw(base.forceActor<Window>(), layer){}

template <typename T>
int AutoDraw<T>::getLayer() const{
    return drawer.getLayer();
}

template <typename T>
void AutoDraw<T>::setLayer(int layer_){
    drawer.setLayer(layer_);
}

template<typename T>
Window& AutoDraw<T>::getWindow() const{
    return drawer.getWindow();
}

template<typename T>
AutoDraw<T>::~AutoDraw(){
    drawer.scene.deleteActor(drawer);
}
