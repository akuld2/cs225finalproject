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
}

bool Node::operator==(Node zone)
{
    return startingLocation_ == zone.getZone();
}

void Node::setNeighbor(Node* new_node, Edge* new_edge) {
    std::pair<Node*, Edge*> pair = std::pair<Node*, Edge*>(new_node, new_edge);
    neighbors_.insert(pair);
}

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

std::vector<double> Node::retrieveNeighborEdgeData(std::string endLocation)
{
    std::map<Node *, Edge *>::iterator it;
    std::vector<double> values;
    for (it = this->getNeighbors()->begin(); it != this->getNeighbors()->end(); it++)
    {
        if (it->first->getZone() == endLocation) {
            values.push_back(it->second->getFare());
            values.push_back(it->second->getTime());
            values.push_back(it->second->getMiles());
            return values;
        }
    }
    return values;
};
