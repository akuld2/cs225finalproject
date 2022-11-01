#pragma once

#include "Edge.h"
#include <map>
#include <string>

class Node
{
public:
    /**
     * getNeighbors() will return an entire list of neighbors.
     * @return a pointer to a map of nodes and edges.
     */
    std::map<Node, Edge> *getNeighbors();

    /**
     * getZone() will retrieve the zone name
     * @return startingLocation_
     */
    std::string getZone();

private:
    std::string startingLocation_;
    std::map<Node, Edge> neighbors_;
};