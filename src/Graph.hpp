#include "Graph.h"

std::vector<Node*> Graph::getNodes() {
    return nodes_;
}

Graph::Graph(std::vector<Node*> nodes) {
    nodes_ = nodes;
}