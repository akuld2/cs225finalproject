#include "Node.h"
#include <iostream>

Node::Node(std::string startLocation)
{
    startingLocation_ = startLocation;
}

void Node::addEdge(Node &endLocation, Edge &newEdge)
{
    neighbors_[&endLocation] = &newEdge;
}

std::map<Node *, Edge *> *Node::getNeighbors()
{
    return &neighbors_;
}

std::string Node::getZone()
{
    return startingLocation_;
};

Node *Node::retrieveNeighbor(Node *endLocation)
{
    for (auto const &neighbor : neighbors_)
    {
        if (neighbor.first->startingLocation_ == endLocation->getZone())
        {

            return neighbor.first;
        }
    }
    return NULL;
};

Edge *Node::retrieveNeighborEdge(Node *endLocation)
{
    // need to check nullness
    if (endLocation == NULL)
    {
        return NULL;
    }
    return neighbors_.at(endLocation);
};

bool Node::checkNeighborExists(std::string endLocation)
{
    std::map<Node *, Edge *>::iterator it;

    for (it = this->getNeighbors()->begin(); it != this->getNeighbors()->end(); it++)
    {
        if (it->first->getZone() == endLocation) {
            return true;
        }
    }
    return false;
};
