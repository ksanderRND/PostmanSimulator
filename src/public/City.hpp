#pragma once

#include <string>
#include <cmath>
#include <SFML/System/Vector2.hpp>

class City {
public:
    City(std::string name, sf::Vector2f position): name(name), position(position) {}
    
    const sf::Vector2f& getPosition() const { return position; }
    const std::string& getName() const  { return name; }

private:
    std::string name;
    sf::Vector2f position;
};

struct Road {
    int toCityId;
    float length;
};

inline float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    
    auto dx = b.x - a.x;
    auto dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}