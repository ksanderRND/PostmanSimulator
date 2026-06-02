#pragma once

#include "City.hpp"

#include <vector>
#include <SFML/System/Vector2.hpp>

class World {
public:
    World();

    void addCity(const std::string& name, sf::Vector2f pos);
    void addRoad(int fromId, int toId);
    
    size_t getNumberOfCities() const { return cities.size(); }
    const sf::Vector2f& getCityPosition(int id) const { return cities.at(id).getPosition(); }
    const std::vector<Road>& getRoadsToNeighbors(int id) const { return roads.at(id); }
    const std::string& getCityName(int id) const  { return cities.at(id).getName(); }

private:
    std::vector<City> cities;
    std::vector<std::vector<Road>> roads;// aka Adjacency List

    void initializeWithTestSample();
};