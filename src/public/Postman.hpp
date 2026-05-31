#pragma once

#include "Config.hpp"
#include "City.hpp"
#include "Navigator.hpp"

#include <vector>
#include <SFML/System/Vector2.hpp>

class Postman {
public:

    enum class PColor{ Red, Green, Blue, Yellow };

    Postman(PColor pColor, sf::Vector2f startPosition, 
        NavigatorType navType = NavigatorType::Dijkstra);

    const sf::Vector2f& getPosition() const { return position; }
    const std::vector<int>& getRoute() const { return route; }
    const sf::Color& getColor() const { return color; }
    std::string getAlgorithmName() const { return navigator->getAlgorithmName(); }
    const Navigator& getNavigator() const { return *navigator; }
    int getCurrentWaypointId() const;
    int getTargetCity() const;

    void setRoute(std::vector<int> newRoute) { route = std::move(newRoute); }
    void resetWaypointIndex() { currentWaypointIndex=0; }

    bool hasEmptyRoute() const { return route.empty(); }
    bool isRouteComplete() const { return currentWaypointIndex >= route.size(); }

    void moveTowards(sf::Vector2f target, float dt);

private:
    std::unique_ptr<Navigator> navigator;
    sf::Vector2f position;
    std::vector<int> route;
    size_t currentWaypointIndex = 0;
    float speed = Config::DEFAULT_POSTMAN_SPEED;
    sf::Color color;
};
