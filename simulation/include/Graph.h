#pragma once

#include "Node.h"

#include <vector>
#include <unordered_map>
#include <memory>   // shared_ptr

/**
 * Edge — a directed weighted connection between two nodes.
 * Weight = physical distance between the two nodes (in meters).
 */
struct Edge {
    int    toId;    // destination node ID
    double weight;  // physical distance in meters
};

/**
 * Graph — the IoT network.
 *
 * Nodes are stored as shared_ptr<Node> so callers can safely hold
 * references without worrying about lifetime.
 *
 * Responsibilities:
 *  - Add / remove nodes
 *  - Build edges between nodes that are within communication range
 *  - Rebuild topology when a node moves
 *  - Provide adjacency list to routing algorithms
 */
class Graph {
public:
    Graph() = default;

    // ── Node management ──────────────────────────────────────────────────────

    // Add a node (takes ownership via shared_ptr)
    void addNode(std::shared_ptr<Node> node);

    // Remove a node (also removes all edges involving it)
    void removeNode(int nodeId);

    // Get a node by ID — returns nullptr if not found
    std::shared_ptr<Node> getNode(int nodeId) const;

    // Get all nodes
    const std::vector<std::shared_ptr<Node>>& getNodes() const;

    // ── Edge management ──────────────────────────────────────────────────────

    // Build (or rebuild) ALL edges based on current node positions
    void buildEdges();

    // Rebuild only the edges for a specific node (cheaper after a single move)
    void rebuildEdgesForNode(int nodeId);

    // Get all outgoing edges from a given node
    const std::vector<Edge>& getEdges(int nodeId) const;

    // ── Mobility ─────────────────────────────────────────────────────────────

    // Move a node to a new position and rebuild its edges
    void moveNode(int nodeId, double newX, double newY);

    // ── Utilities ────────────────────────────────────────────────────────────

    int  nodeCount() const;
    int  edgeCount() const;
    void print()     const;

private:
    std::vector<std::shared_ptr<Node>>                 _nodes;
    std::unordered_map<int, std::vector<Edge>>         _adjacency;  // nodeId → edges

    // Find a node by ID — returns nullptr if not found
    std::shared_ptr<Node> findNode(int nodeId) const;

    // Add an undirected edge between two nodes
    void addEdge(int fromId, int toId, double weight);

    // Remove all edges FROM a given node
    void clearEdgesFrom(int nodeId);

    // Returned when a node has no edges
    static const std::vector<Edge> _emptyEdges;
};
