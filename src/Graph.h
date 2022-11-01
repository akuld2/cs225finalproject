#pragma once

#include "Node.h"
#include <vector>

class Graph {
    public:
        Graph(std::vector<Node*>);
        std::vector<Node*> getNodes();
    private:  
        std::vector<Node*> nodes_;
};