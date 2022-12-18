#include "All.hpp"
#include "AutoDraw.hpp"



// Actor

Scene& Actor::getCurrentCreatingScene(){
    assert(!creatingScenes.empty());
    assert(creatingScenes.back() != nullptr);
    return *creatingScenes.back();
}

Actor::Actor() : scene(getCurrentCreatingScene()){}


// Scene

void Scene::deleteActor(Actor& actor){
    if(shouldIDie) return;
    assert(std::find(actors.begin(), actors.end(), nullptr) == actors.end());
    auto result = std::find_if(actors.begin(), actors.end(), [&actor](auto&j){return j.get() == &actor;});
    auto tempPtr = result->release();
    actors.erase(result);
    assert(std::find(actors.begin(), actors.end(), nullptr) == actors.end());
    delete tempPtr;
    assert(std::find(actors.begin(), actors.end(), nullptr) == actors.end());
}

const std::vector<std::unique_ptr<Actor>>& Scene::getActors() const{
    return actors;
}

void Scene::update(){
    for(i=0; i<actors.size(); ++i){
        assert(actors[i] != nullptr);
        assert(std::find(actors.begin(), actors.end(), nullptr) == actors.end());

        actors[i]->update();
        if(shouldIDie)
            return;
    }
    // for(auto iter=actors.begin(); iter!=actors.end(); ++iter){
    //     assert(*iter != nullptr);
    //     auto oldPtr = iter->get();
    //     assert(iter->get() != nullptr);
    //     (*iter)->update();
    //     if(shouldIDie)
    //         return;
    //     if(vectorChanged){
    //         vectorChanged = false;
    //         for(iter=actors.begin(); iter!=actors.end(); ++iter){
    //             if(iter->get() == oldPtr)
    //                 break;
    //             assert(iter!=actors.end());
    //         }
    //     }
    // }
}

const std::string& Scene::getName() const{
    return name;
}

void Scene::setName(const std::string& name_){
    Scene::name = name_;
}

Scene::Scene(const std::string& name)
    : name(name)
    , shouldIDie(false){}

void Scene::condemnToDeath(){
    shouldIDie = true;
}


// Base

Scene& Base::newScene(const std::string& name){
    return *scenes.emplace_back(std::make_unique<Scene>(name));
}

Scene& Base::newActiveScene(const std::string& name){
    auto& scene = newScene(name);
    setActiveScene(scene);
    return scene;
}

void Base::setActiveScene(Scene& scene){
    assert(std::find_if(scenes.begin(), scenes.end(), [&scene](auto& i){return i.get()==&scene;}) != scenes.end()); // Scena spoza bazy
    activeScene = &scene;
}

Scene* Base::getActiveScene(){
    return activeScene;
}

void Base::deleteScene(Scene& scene){
    auto iter = std::find_if(scenes.begin(), scenes.end(), [&scene](auto& i){return i.get()==&scene;});
    if(iter != scenes.end()){
        scene.condemnToDeath();
        if(iter->get() == activeScene)
            activeScene = nullptr;
        scenes.erase(iter);
    }
}

const std::vector<std::unique_ptr<Scene>>& Base::getScenes() const{
    return scenes;
}

void Base::updateBase(){
    update();
    if(activeScene)
        activeScene->update();
}

Base::Base() noexcept
    : Scene("base")
    , activeScene(nullptr){
   assert(&base == this); // Tylko jedna baza
}

Scene* Base::findScene(const std::string& name){
    auto iter = std::find_if(scenes.begin(), scenes.end(), [&name](auto& i){ return i->getName() == name; });
    if(iter == scenes.end())
        return nullptr;
    return iter->get();
}

Base::~Base(){
    condemnToDeath();
    for(auto& i: scenes)
        i->condemnToDeath();
}


// Window

Window::Window()
    : sf::RenderWindow(sf::VideoMode::getDesktopMode(), "sbngj", sf::Style::Fullscreen){
    setFramerateLimit(30);
}

void Window::drawMe(const sf::Drawable& drawable, int layer){
    drawables.emplace_back(std::pair(&drawable, layer));
}

void Window::update(){
    sf::Event event{};
    while(pollEvent(event))
        if(event.type == sf::Event::Closed)
            close();

    std::sort(drawables.begin(), drawables.end(), [](auto& a, auto& b){ return a.second < b.second; });

    clear();
    for(auto& i: drawables)
        draw(*i.first);
    display();

    drawables.clear();
}

void Window::dontDrawMe(const sf::Drawable& drawable){
    auto iter = std::find_if(drawables.begin(), drawables.end(), [&drawable](auto&i){return i.first == &drawable;});
    if(iter != drawables.end())
        drawables.erase(iter);
}


// Drawer

void Drawer::update(){
    window.drawMe(drawable, layer);
}

int Drawer::getLayer() const{
    return layer;
}

void Drawer::setLayer(int layer_){
    layer = layer_;
}

Drawer::Drawer(Window& window, const sf::Drawable& drawable, int layer)
    : window(window)
    , drawable(drawable)
    , layer(layer){}

Window& Drawer::getWindow() const{
    return window;
}

Drawer::~Drawer(){
    window.dontDrawMe(drawable);
}

