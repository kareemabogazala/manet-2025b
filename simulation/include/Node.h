#pragma once

#include <string>

/**
 * Node — represents a phone/device in the IoT network.
 *
 * Each node has:
 *  - a unique integer ID
 *  - a 2D position (x, y) in meters (GPS-like coordinates)
 *  - a communication range (radius in meters)
 *  - a moving flag — true while the node is in transit
 */
class Node {
public:
    // Constructor
    Node(int id, double x, double y, double range = 100.0);

    // Getters
    int     getId()     const;
    double  getX()      const;
    double  getY()      const;
    double  getRange()  const;
    bool    isMoving()  const;

    // Setters
    void setMoving(bool moving);

    // Move the node to a new position
    void moveTo(double newX, double newY);

    // Euclidean distance to another node (in meters)
    double distanceTo(const Node& other) const;

    // Check if another node is within communication range
    bool isInRange(const Node& other) const;

    // Human-readable string
    std::string toString() const;

private:
    int    _id;
    double _x;
    double _y;
    double _range;
    bool   _moving;
};
