#include "Graph.h"

std::vector<Node*> Graph::getNodes() {
    return nodes_;
}

unsigned int Graph::getSize() {
    return nodes_.size();
}

Node* Graph::getNode(std::string zone) {
    for (unsigned i = 0; i < nodes_.size(); ++i) {
        if (nodes_.at(i)->getZone() == zone) {
            return nodes_.at(i);
        }
    }
    return NULL;
}

Graph::Graph(int if_neg_1) {
    if(if_neg_1 == -1) {
        nodes_.push_back(nullptr);
    }
}

Graph::Graph(std::vector<Node*> nodes) {
    nodes_ = nodes;
}