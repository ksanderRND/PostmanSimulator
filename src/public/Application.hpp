#pragma once


#include <SFML/Graphics.hpp>

#include "Config.hpp"
#include "World.hpp"
#include "Renderer.hpp"
#include "Simulation.hpp"

class Application {
public:
    Application();

    void run();

private:
    sf::RenderWindow window;
    World world;
    Simulation simulation;
    Renderer renderer;

    void handleEvents();
};