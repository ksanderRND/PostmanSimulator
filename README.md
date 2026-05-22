# PostmanSimulator

Pathfinding visualization built with C++17 and SFML 2.6. A postman navigates a connected weighted graph of cities, where all roads are bidirectional and weighted by Euclidean distance. The shortest route between cities is computed using Dijkstra's algorithm and rendered in real-time.

## Roadmap

- **Navigator module** — extract pathfinding from `World` into a dedicated class with a strategy interface
- **Additional algorithms** — BFS, DFS, and A* as pathfinding strategies
- **Multiple postmen** — per-postman color, spawn multiple agents on the map
- **Stronger data model** — encapsulate City, Road, Postman with proper invariants
- **Map loading** — read city/road layouts from file instead of hardcoded test data

## Third-party assets

- [SFML 2.6](https://www.sfml-dev.org/) — licensed under the [zlib/png license](https://www.sfml-dev.org/license/)
- [Arimo](https://github.com/googlefonts/Arimo) font by Steve Matteson — licensed under the [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0)
