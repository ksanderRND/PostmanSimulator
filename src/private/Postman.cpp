#include "Postman.hpp"

Postman::Postman(sf::Color pColor, sf::Vector2f startPosition, NavigatorType navType): 
    color(pColor), position(startPosition), navigator(Navigator::create(navType)) {}

int Postman::getCurrentWaypointId() const
{
    if(hasEmptyRoute()) return 0;
    return isRouteComplete() ? route.back() : route[currentWaypointIndex];
}

int Postman::getTargetCity() const
{
    return hasEmptyRoute() ? 0 : route.back();
}

void Postman::moveTowards(sf::Vector2f target, float dt)
{

    float dist = distance(position, target);
    if (dist < Config::SNAP_DISTANCE) {
        position = target;
        currentWaypointIndex++;
        return;
    }

    sf::Vector2f direction = (target - position)/dist;
    float step = speed * dt;
    if (step >= dist) {
        position = target;
        currentWaypointIndex++;
    } else {
        position += direction * step;
    }
}
