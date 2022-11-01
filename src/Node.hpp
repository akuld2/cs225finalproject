#include "Node.h"

std::map<Node*, Edge*> Node::getNeighbors() {
    return neighbors_;
}