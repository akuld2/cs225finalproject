#include "Graph.h"

std::vector<Node>* Graph::getNodes() {
    return &nodes_;
}

Node* Graph::getNode(std::string zone) {
    for (unsigned i = 0; i < nodes_.size(); ++i) {
        if (nodes_.at(i).getZone() == zone) {
            return &nodes_.at(i);
        }
    }
    return NULL;

}