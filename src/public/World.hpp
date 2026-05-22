#pragma once

#include "Config.hpp"
#include "City.hpp"
#include "Postman.hpp"

#include <vector>
#include <SFML/System/Vector2.hpp>

class World {
public:
    World() = default;
    void initializeWithTestSample();

    void addCity(const std::string& name, sf::Vector2f pos);
    void addRoad(int fromId, int toId);
    void addPostman(Postman::PColor color, sf::Vector2f startPosition = {0,0});
    
    size_t getNumberOfCities() const { return cities.size(); }
    const City& getCity(int id) const { return cities.at(id); }
    const sf::Vector2f& getCityPosition(int id) const { return cities.at(id).getPosition(); }
    const std::vector<Road>& getRoadsToNeighbors(int id) const { return roads.at(id); }
    const std::string& getCityName(int id) const  { return cities.at(id).getName(); }
    std::vector<Postman>& getPostmen() { return postmen; }
    const std::vector<Postman>& getPostmen() const { return postmen; }

    std::vector<int> getRouteDijkstra (int fromId, int toId);

private:
    std::vector<City> cities;
    std::vector<std::vector<Road>> roads;// aka Adjacency List
    std::vector<Postman> postmen;

    std::vector<int> reconstructPath(int toId, const std::vector<int>& parent);
};