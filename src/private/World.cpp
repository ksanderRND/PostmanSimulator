#include "World.hpp"

#include <cassert>
#include <limits>
#include <queue>
#include <iostream>

constexpr int NO_PARENT = -1;

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

    float dist = distance(cities[fromId].position, cities[toId].position);
    roads[fromId].push_back({toId, dist});
    roads[toId].push_back({fromId, dist});
}

void World::addPostman(const Postman &postman)
{
    postmen.push_back(postman);
}

std::vector<int> World::getRouteDijkstra (int fromId, int toId)
{
    if((fromId < 0) || (fromId >= cities.size()) || (toId < 0) || (toId >= cities.size()) ){
        std::cerr<<"path out of range!"<<std::endl;
        return {};
    }

    if (fromId == toId) {
        return {fromId};
    }

    size_t n = cities.size();
    std::vector<float> distances(n, std::numeric_limits<float>::infinity());
    std::vector<int> previous(n, NO_PARENT);
    std::priority_queue<std::pair<float, int>,
                                    std::vector<std::pair<float, int>>,
                                    std::greater<>> pq;

    distances[fromId] = 0.0f;
    pq.push({0.0f, fromId});

    while (!pq.empty()) {
        auto [currentDist, current] = pq.top();
        pq.pop();

        if (current == toId) {
            return reconstructPath(toId, previous);
        }

        if (currentDist > distances[current]) {
            continue;
        }

        for (const Road& road : roads[current]) {
            float newDist = distances[current] + road.length;

            if (newDist < distances[road.toCityId]) {
                distances[road.toCityId] = newDist;
                previous[road.toCityId] = current;
                pq.push({newDist, road.toCityId});
            }
        }
    }

    return {};
}

std::vector<int> World::reconstructPath(int toId, const std::vector<int>& parent) 
{
    std::vector<int> path;
    for (int node = toId; node != NO_PARENT; node = parent[node]) {
        path.push_back(node);
    }
    std::reverse(path.begin(), path.end());
    return path;
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



    Postman postman;
    postman.position = cities[0].position;
    postman.speed = Config::DEFAULT_POSTMAN_SPEED;
    postmen.push_back(postman);
}