#include "Graph.h"
#include <algorithm>

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

int Graph::minDistance(Node* first, Node* second) {
    int minimum_dist = INT16_MAX;
    if (first->getNeighbors()[second]) {
        for (auto it = first->getNeighbors().begin(); it != first->getNeighbors().end(); it++) {
            minimum_dist = std::min(minimum_dist, minDistance(it->first, second) + 1);
        }
    }
    else {
        return 0;
    }
}

std::vector<Node*> Graph::findShortestPath(Node* start, Node* end) {
    return std::vector<Node*>();
}