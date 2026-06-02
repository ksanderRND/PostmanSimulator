#include "Navigator.hpp"
#include "World.hpp"

#include <queue>
#include <limits>
#include <algorithm>
#include <stack>

constexpr int NO_PARENT = -1;

std::unique_ptr<Navigator> Navigator::create(NavigatorType type) {
    switch (type) {
        case NavigatorType::Dijkstra: return std::make_unique<DijkstraNavigator>();
        case NavigatorType::AStar:    return std::make_unique<AStarNavigator>();
        case NavigatorType::BFS:      return std::make_unique<BFSNavigator>();
        case NavigatorType::DFS:      return std::make_unique<DFSNavigator>();
    }
    return std::make_unique<DijkstraNavigator>();
}

std::vector<int> Navigator::reconstructPath(int toId, const std::vector<int> &parent) const {
    std::vector<int> path;
    for (int node = toId; node != NO_PARENT; node = parent[node]) {
        path.push_back(node);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// ==================== Dijkstra ====================
std::vector<int> DijkstraNavigator::findRoute(const World& world, int fromId, int toId) const {

    size_t n = world.getNumberOfCities();

    if (fromId < 0 || fromId >= (int)n || toId < 0 || toId >= (int)n) return {};
    if (fromId == toId) return {fromId};

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

        if (current == toId) return reconstructPath(toId, previous);
        if (currentDist > distances[current]) continue;

        for (const Road& road : world.getRoadsToNeighbors(current)) {
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

// ==================== A* ====================
std::vector<int> AStarNavigator::findRoute(const World& world, int fromId, int toId) const {

    size_t n = world.getNumberOfCities();

    if (fromId < 0 || fromId >= (int)n || toId < 0 || toId >= (int)n) return {};
    if (fromId == toId) return {fromId};

    const sf::Vector2f& goalPos = world.getCityPosition(toId);

    std::vector<float> gScore(n, std::numeric_limits<float>::infinity());
    std::vector<float> fScore(n, std::numeric_limits<float>::infinity());
    std::vector<int> previous(n, NO_PARENT);

    std::priority_queue<std::pair<float, int>,
                        std::vector<std::pair<float, int>>,
                        std::greater<>> pq;

    gScore[fromId] = 0.0f;
    fScore[fromId] = distance(world.getCityPosition(fromId), goalPos);
    pq.push({fScore[fromId], fromId});

    while (!pq.empty()) {
        auto [currentFScore, current] = pq.top();
        pq.pop();

        if (current == toId) return reconstructPath(toId, previous);

        if (currentFScore > fScore[current]) continue;

        for (const Road& road : world.getRoadsToNeighbors(current)) {
            float tentativeG = gScore[current] + road.length;
            if (tentativeG < gScore[road.toCityId]) {
                previous[road.toCityId] = current;
                gScore[road.toCityId] = tentativeG;
                fScore[road.toCityId] = tentativeG + distance(world.getCityPosition(road.toCityId), goalPos);
                pq.push({fScore[road.toCityId], road.toCityId});
            }
        }
    }
    return {};
}

// ==================== BFS ====================
std::vector<int> BFSNavigator::findRoute(const World& world, int fromId, int toId) const {

    size_t n = world.getNumberOfCities();

    if (fromId < 0 || fromId >= (int)n || toId < 0 || toId >= (int)n) return {};
    if (fromId == toId) return {fromId};

    std::vector<int> previous(n, NO_PARENT);
    std::vector<bool> visited(n, false);
    std::queue<int> q;

    visited[fromId] = true;
    q.push(fromId);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == toId) return reconstructPath(toId, previous);

        for (const Road& road : world.getRoadsToNeighbors(current)) {
            if (!visited[road.toCityId]) {
                visited[road.toCityId] = true;
                previous[road.toCityId] = current;
                q.push(road.toCityId);
            }
        }
    }
    return {};
}

// ==================== DFS ====================
std::vector<int> DFSNavigator::findRoute(const World& world, int fromId, int toId) const {

    size_t n = world.getNumberOfCities();

    if (fromId < 0 || fromId >= (int)n || toId < 0 || toId >= (int)n) return {};
    if (fromId == toId) return {fromId};

    std::vector<int> previous(n, NO_PARENT);
    std::vector<bool> visited(n, false);
    std::stack<int> s;

    s.push(fromId);

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        if (visited[current]) continue;
        visited[current] = true;

        if (current == toId) return reconstructPath(toId, previous);

        for (const Road& road : world.getRoadsToNeighbors(current)) {
            if (!visited[road.toCityId]) {
                previous[road.toCityId] = current;
                s.push(road.toCityId);
            }
        }
    }
    return {};
}