#pragma once

#include <random>

#include "World.hpp"
#include "Postman.hpp"


class Simulation {
public:
    Simulation(World& world);

    void update(float dt);

    const std::vector<Postman>& getPostmen() const { return postmen; }

private:
    World& world;
    std::mt19937 rng;
    std::vector<Postman> postmen;
    int startCityId = 0;
    int targetCityId = 0;

    void givePostmanNextRoute(Postman& postman, int currentTargetId, int newTargetId);
    int getNextRandomTarget(int currentTargetId);
};