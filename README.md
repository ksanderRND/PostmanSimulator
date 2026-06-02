# PostmanSimulator

Pathfinding visualization built with C++17 and SFML 2.6. Multiple postmen race across a connected weighted graph of cities, each using a different pathfinding algorithm (BFS, DFS, Dijkstra, A*). All roads are bidirectional and weighted by Euclidean distance. Routes are computed and rendered in real-time, showing how algorithms compare on the same source–destination pair.

## Roadmap

- **Map loading** — read city/road layouts from file instead of hardcoded test data

## Third-party assets

- [SFML 2.6](https://www.sfml-dev.org/) — licensed under the [zlib/png license](https://www.sfml-dev.org/license/)
- [Arimo](https://github.com/googlefonts/Arimo) font by Steve Matteson — licensed under the [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0)
