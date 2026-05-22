#include "Simulation.hpp"
#include "Config.hpp"

#include <chrono>
#include <iostream>

Simulation::Simulation(World &world): 
    world(world), 
    rng(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count())) {}


void Simulation::update(float dt)
{
    for (auto& postman : world.getPostmen()) {
        updatePostman(postman, dt);
    }
}

void Simulation::updatePostman(Postman& postman, float dt) {

    if (postman.route.empty() || postman.currentWaypointIndex >= postman.route.size() ) {
        givePostmanNextRoute(postman);
        return;
    }

    int waypointId = postman.route[postman.currentWaypointIndex];
    moveTowards(postman, world.getCityPosition(waypointId), dt);
}

void Simulation::moveTowards(Postman& postman, sf::Vector2f target, float dt) {

    float dist = distance(postman.position, target);
    if (dist < Config::SNAP_DISTANCE) {
        postman.position = target;
        postman.currentWaypointIndex++;
        return;
    }

    sf::Vector2f direction = (target - postman.position)/dist;
    float step = postman.speed * dt;
    if (step >= dist) {
        postman.position = target;
        postman.currentWaypointIndex++;
    } else {
        postman.position += direction * step;
    }
}

void Simulation::givePostmanNextRoute(Postman& postman) {
    int currentTargetId = postman.route.empty() ? 0 : postman.route.back();
    int newTargetId = getNextRandomTarget(currentTargetId);
    postman.route = world.getRouteDijkstra(currentTargetId, newTargetId);
    if (postman.route.empty() ) { std::cerr<<"No path found for: "<<currentTargetId<<std::endl; }
    postman.currentWaypointIndex = 0;
}

int Simulation::getNextRandomTarget(int currentTargetId)
{
    int cityCount = world.getNumberOfCities();

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
