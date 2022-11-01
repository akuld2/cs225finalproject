#include "Node.h"

std::map<Node, Edge> *Node::getNeighbors()
{
    return &neighbors_;
}

std::string Node::getZone()
{
    return startingLocation_;
};

Node Node::retrieveNeighbor(Node endLocation)
{
    for (auto const &neighbor : neighbors_)
    {
        if (neighbor.first.startingLocation_ == endLocation.getZone())
        {
            return neighbor.first;
        }
    }

    return Node();
};

bool Node::operator==(Node zone)
{
    return startingLocation_ == zone.getZone();
};