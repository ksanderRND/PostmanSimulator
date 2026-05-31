#include "Postman.hpp"

Postman::Postman(PColor pColor, sf::Vector2f startPosition, NavigatorType navType): position(startPosition), navigator(Navigator::create(navType))
{
    switch (pColor)
    {
    case PColor::Red:
        color = sf::Color::Red;
        break;
    case PColor::Green:
        color = sf::Color::Green;
        break;
    case PColor::Blue:
        color = sf::Color::Blue;
        break;
    case PColor::Yellow:
        color = sf::Color::Yellow;
        break;
    default:
        color = sf::Color::Red;
        break;
    }
}

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
