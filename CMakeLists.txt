cmake_minimum_required(VERSION 3.15)
project(gj)

set(CMAKE_CXX_FLAGS -pedantic-errors)

set(CMAKE_CXX_STANDARD 20)

add_executable(gj code/main.cpp code/base/Actor.hpp code/base/Scene.hpp code/base/AutoDraw.hpp code/base/Base.hpp code/base/ResourceBank.hpp code/base/Base.cpp code/base/All.hpp code/base/AnimatedSprite.cpp code/base/AnimatedSprite.hpp code/Player.cpp code/Player.hpp code/Enums.hpp code/Terrain.cpp code/Terrain.hpp code/Bullet.cpp code/Bullet.hpp code/MainGame.cpp code/MainGame.hpp code/Animal.cpp code/Animal.hpp code/GameManager.cpp code/GameManager.hpp code/Menu.cpp code/Menu.hpp code/Kabum.cpp code/Kabum.h code/WinScreen.cpp code/WinScreen.hpp code/Audio.cpp code/Audio.hpp)

target_link_libraries(gj sfml-window sfml-graphics sfml-system sfml-audio)
