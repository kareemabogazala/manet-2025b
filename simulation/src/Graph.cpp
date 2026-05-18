#include "Graph.h"

#include <iostream>
#include <algorithm>

// ── Static member ──────────────────────────────────────────────────────────────

const std::vector<Edge> Graph::_emptyEdges;

// ── Node management ────────────────────────────────────────────────────────────

void Graph::addNode(std::shared_ptr<Node> node) {
    // Guard: don't add duplicate IDs
    if (findNode(node->getId()) != nullptr) {
        std::cerr << "[Graph] Node " << node->getId() << " already exists.\n";
        return;
    }
    _nodes.push_back(node);
    _adjacency[node->getId()] = {};  // empty edge list for new node
}

void Graph::removeNode(int nodeId) {
    // Remove from node list
    _nodes.erase(
        std::remove_if(_nodes.begin(), _nodes.end(),
            [nodeId](const std::shared_ptr<Node>& n) { return n->getId() == nodeId; }),
        _nodes.end()
    );

    // Remove its own adjacency entry
    _adjacency.erase(nodeId);

    // Remove all edges pointing TO this node from other nodes
    for (auto& [id, edges] : _adjacency) {
        edges.erase(
            std::remove_if(edges.begin(), edges.end(),
                [nodeId](const Edge& e) { return e.toId == nodeId; }),
            edges.end()
        );
    }
}

std::shared_ptr<Node> Graph::getNode(int nodeId) const {
    return findNode(nodeId);
}

const std::vector<std::shared_ptr<Node>>& Graph::getNodes() const {
    return _nodes;
}

// ── Edge management ────────────────────────────────────────────────────────────

void Graph::buildEdges() {
    // Clear all existing edges
    for (auto& [id, edges] : _adjacency) {
        edges.clear();
    }

    // For every pair of nodes, connect them if they are in range
    for (size_t i = 0; i < _nodes.size(); ++i) {
        for (size_t j = i + 1; j < _nodes.size(); ++j) {
            const auto& a = _nodes[i];
            const auto& b = _nodes[j];
            if (a->isInRange(*b)) {
                double dist = a->distanceTo(*b);
                addEdge(a->getId(), b->getId(), dist);
            }
        }
    }
}

void Graph::rebuildEdgesForNode(int nodeId) {
    auto node = findNode(nodeId);
    if (!node) return;

    // Clear edges FROM this node and edges pointing TO this node
    clearEdgesFrom(nodeId);
    for (auto& [id, edges] : _adjacency) {
        if (id == nodeId) continue;
        edges.erase(
            std::remove_if(edges.begin(), edges.end(),
                [nodeId](const Edge& e) { return e.toId == nodeId; }),
            edges.end()
        );
    }

    // Rebuild edges between this node and all others
    for (const auto& other : _nodes) {
        if (other->getId() == nodeId) continue;
        if (node->isInRange(*other)) {
            double dist = node->distanceTo(*other);
            addEdge(nodeId, other->getId(), dist);
        }
    }
}

const std::vector<Edge>& Graph::getEdges(int nodeId) const {
    auto it = _adjacency.find(nodeId);
    if (it == _adjacency.end()) return _emptyEdges;
    return it->second;
}

// ── Mobility ───────────────────────────────────────────────────────────────────

void Graph::moveNode(int nodeId, double newX, double newY) {
    auto node = findNode(nodeId);
    if (!node) {
        std::cerr << "[Graph] moveNode: Node " << nodeId << " not found.\n";
        return;
    }
    node->moveTo(newX, newY);
    rebuildEdgesForNode(nodeId);
}

// ── Utilities ──────────────────────────────────────────────────────────────────

int Graph::nodeCount() const {
    return static_cast<int>(_nodes.size());
}

int Graph::edgeCount() const {
    int total = 0;
    for (const auto& [id, edges] : _adjacency) {
        total += static_cast<int>(edges.size());
    }
    // Each undirected edge is stored twice (from A→B and B→A), so divide by 2
    return total / 2;
}

void Graph::print() const {
    std::cout << "=== Network Graph ===\n";
    std::cout << "Nodes: " << nodeCount() << "  Edges: " << edgeCount() << "\n";
    for (const auto& node : _nodes) {
        std::cout << "  " << node->toString() << "\n";
        for (const auto& edge : getEdges(node->getId())) {
            std::cout << "    --> Node[" << edge.toId
                      << "]  dist=" << edge.weight << "m\n";
        }
    }
    std::cout << "=====================\n";
}

// ── Private helpers ────────────────────────────────────────────────────────────

std::shared_ptr<Node> Graph::findNode(int nodeId) const {
    for (const auto& n : _nodes) {
        if (n->getId() == nodeId) return n;
    }
    return nullptr;
}

void Graph::addEdge(int fromId, int toId, double weight) {
    _adjacency[fromId].push_back({toId,   weight});
    _adjacency[toId].push_back  ({fromId, weight});
}

void Graph::clearEdgesFrom(int nodeId) {
    auto it = _adjacency.find(nodeId);
    if (it != _adjacency.end()) {
        it->second.clear();
    }
}
