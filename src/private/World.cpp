#include "World.hpp"

#include <cassert>
#include <iostream>

void World::addCity(const std::string &name, sf::Vector2f pos)
{
    cities.push_back({name, pos});
    roads.emplace_back();
}

void World::addRoad(int fromId, int toId)
{
    assert(fromId < cities.size() && "addRoad: invalid source CityId");
    assert(toId < cities.size() && "addRoad: invalid destination CityId");
    assert(fromId != toId && "addRoad: self-loop not allowed");

    // Skip duplicate edges
    for (const auto& road : roads[fromId]) {
        if (road.toCityId == toId) return;
    }

    float dist = distance(cities[fromId].getPosition(), cities[toId].getPosition());
    roads[fromId].push_back({toId, dist});
    roads[toId].push_back({fromId, dist});
}

void World::addPostman(Postman::PColor color, sf::Vector2f startPosition, NavigatorType navType)
{
    postmen.push_back({color, startPosition, navType});
}

void World::initializeWithTestSample()
{
    // Left cluster
    addCity("A1", {80, 100});      // 0
    addCity("A2", {200, 150});     // 1
    addCity("A3", {120, 280});     // 2

    // Central hub
    addCity("B1", {350, 120});   // 3
    addCity("B2", {380, 200});   // 4
    addCity("B3", {320, 300});   // 5

    // Right cluster
    addCity("C1", {580, 80});      // 6
    addCity("C2", {720, 150});     // 7
    addCity("C3", {650, 350});     // 8

    // Remote cities
    addCity("D1", {500, 400});   // 9
    addCity("D2", {150, 450});   // 10
    addCity("D3", {600, 250});   // 11

    // Left cluster internal
    addRoad(0, 1);
    addRoad(1, 2);

    // Left cluster to hub
    addRoad(1, 3);
    addRoad(2, 4);

    // Hub internal — triangle for multiple route options
    addRoad(3, 4);
    addRoad(4, 5);
    addRoad(3, 5);

    // Hub to right cluster
    addRoad(3, 6);
    addRoad(4, 11);

    // Right cluster internal
    addRoad(6, 7);
    addRoad(7, 8);
    addRoad(6, 8);

    // Long alternative routes through remote cities
    addRoad(11, 8);
    addRoad(5, 9);
    addRoad(9, 8);

    // Southern corridor
    addRoad(2, 10);
    addRoad(10, 9);

    // Shortcut bypassing left cluster
    addRoad(0, 3);

    addPostman(Postman::PColor::Blue,   cities[0].getPosition(), NavigatorType::Dijkstra);
    addPostman(Postman::PColor::Green,  cities[0].getPosition(), NavigatorType::AStar);
    addPostman(Postman::PColor::Red,    cities[0].getPosition(), NavigatorType::BFS);
    addPostman(Postman::PColor::Yellow, cities[0].getPosition(), NavigatorType::DFS);
}