#pragma once

#include "IRoutingAlgorithm.h"

/**
 * LocationDijkstra — our proposed routing algorithm.
 *
 * Runs Dijkstra's algorithm on the network graph where the edge weight
 * is the physical distance (in meters) between two nodes.
 *
 * The shortest path minimizes total physical distance traveled,
 * as opposed to hop count (used by baseline algorithms).
 */
class LocationDijkstra : public IRoutingAlgorithm {
public:
    LocationDijkstra() = default;
    ~LocationDijkstra() override = default;

    /**
     * Find the shortest physical-distance path from srcId to dstId.
     */
    RoutingResult run(const Graph& graph, int srcId, int dstId) const override;

    std::string name() const override;
};
