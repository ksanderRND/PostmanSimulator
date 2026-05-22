#pragma once

#include "Config.hpp"

#include <vector>
#include <string>
#include <cmath>
#include <SFML/System/Vector2.hpp>

struct City {
    std::string name;
    sf::Vector2f position;
};

struct Road {
    int toCityId;
    float length;
};

struct Postman {
    sf::Vector2f position;

    std::vector<int> route;
    size_t currentWaypointIndex = 0;

    float speed = Config::DEFAULT_POSTMAN_SPEED;
};

inline float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    auto dx = b.x - a.x;
    auto dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}

class World {
public:
    World() = default;
    void initializeWithTestSample();

    void addCity(const std::string& name, sf::Vector2f pos);
    void addRoad(int fromId, int toId);
    void addPostman(const Postman& postman);
    
    size_t getNumberOfCities() const { return cities.size(); }
    const City& getCity(int id) const { return cities.at(id); }
    const sf::Vector2f& getCityPosition(int id) const { return cities.at(id).position; }
    const std::vector<Road>& getRoadsToNeighbors(int id) const { return roads.at(id); }
    const std::string& getCityName(int id) const  { return cities.at(id).name; }
    std::vector<Postman>& getPostmen() { return postmen; }
    const std::vector<Postman>& getPostmen() const { return postmen; }

    std::vector<int> getRouteDijkstra (int fromId, int toId);

private:
    std::vector<City> cities;
    std::vector<std::vector<Road>> roads;// aka Adjacency List
    std::vector<Postman> postmen;

    std::vector<int> reconstructPath(int toId, const std::vector<int>& parent);
};