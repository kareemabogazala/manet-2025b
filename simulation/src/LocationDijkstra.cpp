#include "LocationDijkstra.h"

#include <unordered_map>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

// ── Dijkstra (distance-weighted) ───────────────────────────────────────────────

RoutingResult LocationDijkstra::run(const Graph& graph, int srcId, int dstId) const {
    RoutingResult result;

    const auto& nodes = graph.getNodes();
    if (nodes.empty()) return result;

    // ── 1. Initialize data structures ──────────────────────────────────────────

    constexpr double INF = std::numeric_limits<double>::infinity();

    // dist[nodeId] = shortest known distance from src to nodeId
    std::unordered_map<int, double> dist;

    // prev[nodeId] = predecessor on the shortest path
    std::unordered_map<int, int> prev;

    for (const auto& node : nodes) {
        dist[node->getId()] = INF;
        prev[node->getId()] = -1;
    }
    dist[srcId] = 0.0;

    // Min-heap: (distance, nodeId)
    using PQEntry = std::pair<double, int>;
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<PQEntry>> pq;
    pq.push({0.0, srcId});

    // ── 2. Dijkstra main loop ──────────────────────────────────────────────────

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Early exit if we reached the destination
        if (u == dstId) break;

        // Skip stale entries
        if (d > dist[u]) continue;

        for (const auto& edge : graph.getEdges(u)) {
            int    v      = edge.toId;
            double newDist = dist[u] + edge.weight;

            if (newDist < dist[v]) {
                dist[v] = newDist;
                prev[v] = u;
                pq.push({newDist, v});
            }
        }
    }

    // ── 3. Reconstruct path ────────────────────────────────────────────────────

    if (dist[dstId] == INF) {
        // No path found
        result.reachable = false;
        return result;
    }

    // Walk back from dst → src via prev[]
    std::vector<int> path;
    for (int cur = dstId; cur != -1; cur = prev[cur]) {
        path.push_back(cur);
    }
    std::reverse(path.begin(), path.end());

    // ── 4. Fill result ─────────────────────────────────────────────────────────

    result.reachable      = true;
    result.path           = path;
    result.totalDistance  = dist[dstId];
    result.hopCount       = static_cast<int>(path.size()) - 1;

    return result;
}

std::string LocationDijkstra::name() const {
    return "Location-Based Dijkstra";
}
