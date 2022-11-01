#include "Node.h"

std::map<Node, Edge> *Node::getNeighbors()
{
    return &neighbors_;
}

std::string Node::getZone()
{
    return startingLocation_;
};

Node *Node::retrieveNeighbor() {

};

bool Node::operator==(Node* zone) {
    return startingLocation_ == zone->getZone();
};