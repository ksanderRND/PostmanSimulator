#include "Renderer.hpp"

#include <iostream>

Renderer::Renderer()
{
    fontLoaded = loadFont();
    if (!fontLoaded) {
        std::cerr << "Warning: Could not load font. Text will not display.\n";
    }
}

bool Renderer::loadFont() {
    return font.loadFromFile(Config::FONT_PATH);
}

void Renderer::render(sf::RenderWindow &window, const World &world)
{
    for (size_t i=0; i < world.getNumberOfCities(); i++) {
        drawCityWithRoads(window, world, i);
    }
    drawPostmen(window, world);
}

void Renderer::drawCityWithRoads(sf::RenderWindow & window, const World &world, const int cityId)
{
    const auto& roads = world.getRoadsToNeighbors(cityId);
    for (const Road& road : roads) {
        if(road.toCityId > cityId) {  // hack to skip double paint lines
            drawRoad(window, world.getCityPosition(cityId), world.getCityPosition(road.toCityId));
        }
    }
            
    drawCity(window, world.getCityPosition(cityId), world.getCityName(cityId));
}

void Renderer::drawRoad(sf::RenderWindow & window, const sf::Vector2f &from, const sf::Vector2f &to, const sf::Color color)
{
    sf::Vertex line[] = {
        sf::Vertex(from, color),
        sf::Vertex(to, color)
    };
    window.draw(line, 2, sf::Lines);
}

void Renderer::drawCity(sf::RenderWindow& window, const sf::Vector2f& position, const std::string& name) {
    sf::CircleShape shape(Config::CITY_RADIUS);
    shape.setOrigin({Config::CITY_RADIUS, Config::CITY_RADIUS});
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(Config::CITY_OUTLINE);
    window.draw(shape);
    
    if(fontLoaded){
        sf::Text text;
        text.setFont(font);
        text.setString(name);
        text.setCharacterSize(Config::TEXT_SIZE);
        text.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
        text.setPosition(position.x, position.y + Config::LABEL_Y_OFFSET);

        window.draw(text);
    }
}

void Renderer::drawPostmen(sf::RenderWindow& window, const World& world) {
    for (const auto& postman : world.getPostmen()) {
        highlightPostmansPath(window, world, postman);
        sf::CircleShape shape(Config::POSTMAN_RADIUS);
        shape.setOrigin({Config::POSTMAN_RADIUS, Config::POSTMAN_RADIUS});
        shape.setPosition(postman.getPosition());
        shape.setFillColor(postman.getColor());
        window.draw(shape);
    }
}

void Renderer::highlightPostmansPath(sf::RenderWindow &window, const World &world, const Postman &postman)
{
    const auto& path = postman.getRoute();
    if(path.empty()) { return; }

    for(size_t i = 0; i+1<path.size(); i++) {
        const int cityFrom = path[i];
        const int cityTo = path[i+1];
        const auto& from = world.getCityPosition(cityFrom);
        const auto& to = world.getCityPosition(cityTo);
        drawRoad(window, from, to, postman.getColor());

    }
    int targetCity = postman.getTargetCity();
    highlightDestinationCity(window, world.getCityPosition(targetCity), postman.getColor());
}

void Renderer::highlightDestinationCity(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Color& postmansColor) {
        sf::CircleShape shape(Config::CITY_RADIUS);
        shape.setOrigin({Config::CITY_RADIUS, Config::CITY_RADIUS});
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Magenta);
        shape.setOutlineColor(postmansColor);
        shape.setOutlineThickness(Config::DEST_CITY_OUTLINE);
        window.draw(shape);
}
