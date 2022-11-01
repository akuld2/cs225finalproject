#include "Node.h"

std::map<Node, Edge>* Node::getNeighbors() {
    return &neighbors_;
}

std::string Node::getZone() {
    return startingLocation_;
};