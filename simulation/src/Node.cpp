#include "Node.h"

#include <cmath>
#include <string>

// ── Constructor ────────────────────────────────────────────────────────────────

Node::Node(int id, double x, double y, double range)
    : _id(id), _x(x), _y(y), _range(range), _moving(false) {}

// ── Getters ────────────────────────────────────────────────────────────────────

int    Node::getId()    const { return _id;     }
double Node::getX()     const { return _x;      }
double Node::getY()     const { return _y;      }
double Node::getRange() const { return _range;  }
bool   Node::isMoving() const { return _moving; }

// ── Setters ────────────────────────────────────────────────────────────────────

void Node::setMoving(bool moving) {
    _moving = moving;
}

// ── Position ───────────────────────────────────────────────────────────────────

void Node::moveTo(double newX, double newY) {
    _x = newX;
    _y = newY;
}

// ── Distance & Range ───────────────────────────────────────────────────────────

double Node::distanceTo(const Node& other) const {
    double dx = _x - other._x;
    double dy = _y - other._y;
    return std::sqrt(dx * dx + dy * dy);
}

bool Node::isInRange(const Node& other) const {
    // Two nodes can communicate if the distance is within BOTH their ranges
    // (use the smaller range as the limiting factor)
    double minRange = std::min(_range, other._range);
    return distanceTo(other) <= minRange;
}

// ── Debug ──────────────────────────────────────────────────────────────────────

std::string Node::toString() const {
    return "Node[" + std::to_string(_id) + "]"
         + " pos=(" + std::to_string(_x) + ", " + std::to_string(_y) + ")"
         + " range=" + std::to_string(_range)
         + (_moving ? " [MOVING]" : "");
}
