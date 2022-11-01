#include "Node.h"

std::map<Node*, Edge*> Node::getNeighbors() {
    return neighbors_;
}
void Node::setNeighbors(Edge* edge) {
    neighbors_.insert(std::pair<Node*, Edge*>(this, edge));
}
