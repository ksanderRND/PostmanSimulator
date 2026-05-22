#pragma once

#include <random>

#include "World.hpp"


class Simulation {
public:
    Simulation(World& world);

    void update(float dt);
private:
    World& world;
    std::mt19937 rng;

    void updatePostman(Postman& postman, float dt);
    void moveTowards(Postman& postman, sf::Vector2f target, float dt);
    void givePostmanNextRoute(Postman& postman);
    int getNextRandomTarget(int currentTargetId);
};