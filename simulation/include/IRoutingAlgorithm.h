#pragma once

#include "Graph.h"

#include <vector>
#include <string>

/**
 * RoutingResult — the output of any routing algorithm run.
 */
struct RoutingResult {
    std::vector<int> path;          // ordered list of node IDs (src → ... → dst)
    double           totalDistance; // sum of physical distances along the path (meters)
    int              hopCount;      // number of hops (edges) in the path
    bool             reachable;     // false if no path exists

    RoutingResult()
        : totalDistance(0.0), hopCount(0), reachable(false) {}
};

/**
 * IRoutingAlgorithm — abstract base class for all routing algorithms.
 *
 * To add a new algorithm:
 *   1. Inherit from IRoutingAlgorithm
 *   2. Implement run() and name()
 *   3. Register it in the simulation
 *
 * This interface ensures every algorithm can be compared on the same network
 * under the same conditions.
 */
class IRoutingAlgorithm {
public:
    virtual ~IRoutingAlgorithm() = default;

    /**
     * Run the algorithm on the given graph.
     *
     * @param graph   The network graph (read-only)
     * @param srcId   Source node ID
     * @param dstId   Destination node ID
     * @return        RoutingResult with path, distance, hop count, reachability
     */
    virtual RoutingResult run(const Graph& graph, int srcId, int dstId) const = 0;

    /**
     * Human-readable name of the algorithm (used in comparison reports).
     */
    virtual std::string name() const = 0;
};
