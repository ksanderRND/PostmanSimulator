#pragma once

#include <SFML/Graphics.hpp>

#include "Config.hpp"
#include "World.hpp"

class Renderer {
public:
    Renderer();
    void render(sf::RenderWindow& window, const World& world);
private:
    bool fontLoaded;
    sf::Font font;
    
    bool loadFont();
    void drawCityWithRoads(sf::RenderWindow& window, const World& world, int cityId);
    void drawRoad(sf::RenderWindow& window, const sf::Vector2f& from, const sf::Vector2f& to, const sf::Color color = sf::Color::White);
    void drawCity(sf::RenderWindow& window, const sf::Vector2f& position, const std::string& name);
    void drawPostmen(sf::RenderWindow& window, const World& world);
    void highlightPostmansPath(sf::RenderWindow& window, const World& world, const Postman& postman);
    void highlightDestinationCity(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Color& postmansColor);
};