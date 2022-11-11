#include "Node.h"
#include <iostream>

Node::Node(std::string startLocation) {
    startingLocation_ = startLocation;
}


void Node::addEdge(Node& endLocation, Edge& newEdge) {
    neighbors_.at(endLocation) = newEdge;
    // std::cout << endLocation << newEdge <<std::endl;
    // (void) endLocation;
    // (void) newEdge;
}

std::map<Node&, Edge&> *Node::getNeighbors()
{
    return &neighbors_;
}

std::string Node::getZone()
{
    return startingLocation_;
};

Node* Node::retrieveNeighbor(Node& endLocation)
{
    for (auto const &neighbor : neighbors_)
    {
        if (neighbor.first.startingLocation_ == endLocation.getZone())
        {
            
            return &neighbor.first;
        }
    }
    return NULL;
};

// @todo need to fix
Edge* Node::retrieveNeighborEdge(Node& endLocation) {
    // need to check nullness
    // if (endLocation == NULL) {
    //     return NULL;
    // }
    return &neighbors_.at(endLocation);
};

bool Node::operator==(Node* zone)
{
    return startingLocation_ == zone->getZone();
};
