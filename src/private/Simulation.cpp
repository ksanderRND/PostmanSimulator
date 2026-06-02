#include "Simulation.hpp"
#include "Config.hpp"

#include <iostream>

Simulation::Simulation(World &world): 
    world(world), rng(std::random_device{}()) {

        sf::Vector2f startPosition = (world.getNumberOfCities() > 0) ? world.getCityPosition(0) : sf::Vector2f {0.0, 0.0};
        postmen.push_back({sf::Color::Green,  startPosition, NavigatorType::AStar});
        postmen.push_back({sf::Color::Blue,   startPosition, NavigatorType::Dijkstra});
        postmen.push_back({sf::Color::Yellow, startPosition, NavigatorType::DFS});
        postmen.push_back({sf::Color::Red,    startPosition, NavigatorType::BFS});
    }

void Simulation::update(float dt)
{
    bool allArrived = true;

    for (auto& postman : postmen) {
        if (postman.hasEmptyRoute() || postman.isRouteComplete()) {
            continue;
        }
        allArrived = false;
        postman.moveTowards(world.getCityPosition(postman.getCurrentWaypointId()), dt);
    }

    if (allArrived) {
        startCityId = targetCityId;
        targetCityId = getNextRandomTarget(startCityId);
        for (auto& postman : postmen) {
            givePostmanNextRoute(postman, startCityId, targetCityId);
        }
    }
}

void Simulation::givePostmanNextRoute(Postman& postman, int currentTargetId, int newTargetId) {
    postman.setRoute(postman.getNavigator().findRoute(world, currentTargetId, newTargetId));
    if (postman.hasEmptyRoute() ) { std::cerr<<"No path found for: "<<currentTargetId<<std::endl; }
    postman.resetWaypointIndex();
}

int Simulation::getNextRandomTarget(int currentTargetId)
{
    size_t cityCount = world.getNumberOfCities();

    if (cityCount <= 1) {
        return currentTargetId;
    }

    std::uniform_int_distribution<int> dist(0, cityCount - 1);

    int newTargetId;
    do {
        newTargetId = dist(rng);
    } while (newTargetId == currentTargetId);

    return newTargetId;
}
