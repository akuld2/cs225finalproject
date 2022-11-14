#include "Node.h"

std::map<Node*, Edge*>* Node::getNeighbors()
{
    return &neighbors_;
}

std::string Node::getZone()
{
    return startingLocation_;
}

Node* Node::retrieveNeighbor(Node* endLocation)
{
    for (auto const neighbor : neighbors_)
    {
        if (neighbor.first->startingLocation_ == endLocation->getZone())
        {
            return neighbor.first;
        }
    }

    return nullptr;
}

Edge* Node::retrieveNeighborEdge(Node* endLocation) {
    if (endLocation == nullptr) {
        return nullptr;
    }
    return neighbors_[endLocation];
}

bool Node::operator==(Node zone)
{
    return startingLocation_ == zone.getZone();
}

Node::Node() {}

Node::Node(std::string start) {
    startingLocation_ = start;
}

void Node::setNeighbor(Node* new_node, Edge* new_edge) {
    std::pair<Node*, Edge*> pair = std::pair<Node*, Edge*>(new_node, new_edge);
    neighbors_.insert(pair);
}