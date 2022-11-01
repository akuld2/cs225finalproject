#pragma once

#include "Edge.h"
#include <map>
#include <string>

class Node {
    public:
        std::map<Node, Edge>* getNeighbors();
    private:
        std::string startingLocation_;
        std::map<Node, Edge> neighbors_;

};