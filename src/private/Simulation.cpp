#include "Simulation.hpp"
#include "Config.hpp"

#include <iostream>

Simulation::Simulation(World &world): 
    world(world), 
    rng(std::random_device{}()) {}


void Simulation::update(float dt)
{
    for (auto& postman : world.getPostmen()) {
        updatePostman(postman, dt);
    }
}

void Simulation::updatePostman(Postman& postman, float dt) {

    if( postman.hasEmptyRoute() || postman.isRouteComplete() ) {
        givePostmanNextRoute(postman);
        return;
    }

    int waypointId = postman.getCurrentWaypointId();
    postman.moveTowards(world.getCityPosition(waypointId), dt);
}

void Simulation::givePostmanNextRoute(Postman& postman) {
    int currentTargetId = postman.getTargetCity();
    int newTargetId = getNextRandomTarget(currentTargetId);
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
