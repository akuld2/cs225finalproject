#pragma once

#include "Node.h"
#include <vector>

class Graph {
    public:
        std::vector<Node>* getNodes();
    private:  
        std::vector<Node> nodes_;
};