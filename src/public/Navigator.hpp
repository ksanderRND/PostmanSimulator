#pragma once

#include <vector>
#include <string>
#include <memory>

class World;

enum class NavigatorType {
    Dijkstra,
    AStar,
    BFS,
    DFS
};

class Navigator {
public:
    virtual ~Navigator() = default;

    static std::unique_ptr<Navigator> create(NavigatorType type);

    virtual std::vector<int> findRoute(const World& world, int fromId, int toId) const = 0;
    virtual std::string getAlgorithmName() const = 0;
    virtual NavigatorType getNavigatorType() const = 0;

protected:
    // Shared helper: reconstruct path from parent array
    std::vector<int> reconstructPath(int toId, const std::vector<int>& parent) const;
};

// ==================== Dijkstra ====================
class DijkstraNavigator : public Navigator {
public:
    std::vector<int> findRoute(const World& world, int fromId, int toId) const override;
    std::string getAlgorithmName() const override { return "Dijkstra"; }
    NavigatorType getNavigatorType() const override { return NavigatorType::Dijkstra; }
};

// ==================== A* ====================
class AStarNavigator : public Navigator {
public:
    std::vector<int> findRoute(const World& world, int fromId, int toId) const override;
    std::string getAlgorithmName() const override { return "A*"; }
    NavigatorType getNavigatorType() const override { return NavigatorType::AStar; }
};

// ==================== BFS ====================
class BFSNavigator : public Navigator {
public:
    std::vector<int> findRoute(const World& world, int fromId, int toId) const override;
    std::string getAlgorithmName() const override { return "BFS"; }
    NavigatorType getNavigatorType() const override { return NavigatorType::BFS; }
};

// ==================== DFS ====================
class DFSNavigator : public Navigator {
public:
    std::vector<int> findRoute(const World& world, int fromId, int toId) const override;
    std::string getAlgorithmName() const override { return "DFS"; }
    NavigatorType getNavigatorType() const override { return NavigatorType::DFS; }
};