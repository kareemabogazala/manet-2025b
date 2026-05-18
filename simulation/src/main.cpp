#include "Graph.h"
#include "LocationDijkstra.h"

#include <iostream>
#include <memory>

// ── Helper: print a RoutingResult ──────────────────────────────────────────────

void printResult(const RoutingResult& result, const std::string& algoName) {
    std::cout << "\n[" << algoName << "]\n";
    if (!result.reachable) {
        std::cout << "  No path found.\n";
        return;
    }
    std::cout << "  Path:     ";
    for (size_t i = 0; i < result.path.size(); ++i) {
        if (i > 0) std::cout << " -> ";
        std::cout << "Node[" << result.path[i] << "]";
    }
    std::cout << "\n";
    std::cout << "  Distance: " << result.totalDistance << " m\n";
    std::cout << "  Hops:     " << result.hopCount << "\n";
}

// ── Main ───────────────────────────────────────────────────────────────────────

int main() {
    std::cout << "=== IoT Routing Simulation — POC ===\n\n";

    // ── 1. Build the network ───────────────────────────────────────────────────
    //
    //   Network layout (each node has range = 150 m):
    //
    //   [0] (0,0) ------- [1] (100,0) ------- [2] (200,0)
    //                          |
    //                     [3] (100,100)
    //                          |
    //                     [4] (100,200)
    //
    // Connections (within 150 m):
    //   0 <-> 1  (100 m)
    //   1 <-> 2  (100 m)
    //   1 <-> 3  (100 m)
    //   3 <-> 4  (100 m)

    Graph graph;

    graph.addNode(std::make_shared<Node>(0,   0.0,   0.0, 150.0));
    graph.addNode(std::make_shared<Node>(1, 100.0,   0.0, 150.0));
    graph.addNode(std::make_shared<Node>(2, 200.0,   0.0, 150.0));
    graph.addNode(std::make_shared<Node>(3, 100.0, 100.0, 150.0));
    graph.addNode(std::make_shared<Node>(4, 100.0, 200.0, 150.0));

    graph.buildEdges();
    graph.print();

    // ── 2. Run Location-Based Dijkstra ─────────────────────────────────────────

    LocationDijkstra algo;

    // Route from Node 0 to Node 4
    RoutingResult r1 = algo.run(graph, 0, 4);
    printResult(r1, algo.name());

    // Route from Node 2 to Node 4
    RoutingResult r2 = algo.run(graph, 2, 4);
    printResult(r2, algo.name());

    // ── 3. Simulate mobility ────────────────────────────────────────────────────

    std::cout << "\n--- Node[3] moves to (300, 300) — out of range of everyone ---\n";
    graph.moveNode(3, 300.0, 300.0);
    graph.print();

    // Try to route from 0 to 4 after Node 3 disconnected
    RoutingResult r3 = algo.run(graph, 0, 4);
    printResult(r3, algo.name());

    std::cout << "\n--- Node[3] moves back to (100, 100) ---\n";
    graph.moveNode(3, 100.0, 100.0);
    graph.print();

    RoutingResult r4 = algo.run(graph, 0, 4);
    printResult(r4, algo.name());

    std::cout << "\n=== Done ===\n";
    return 0;
}
