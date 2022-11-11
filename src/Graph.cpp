#include "Graph.h"
#include <algorithm>
#include <queue>
#include <limits>
#include <iostream>

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

/*double Graph::minDistance(Node* first, Node* second) { //unused
    double minimum_dist = INT16_MAX;
    if (!first->getNeighbors()[second]) {
        for (auto it = first->getNeighbors().begin(); it != first->getNeighbors().end(); it++) {
            minimum_dist = std::min(minimum_dist, minDistance(it->first, second) +
             first->retrieveNeighborEdge(it->first)->getMiles());
        }
    }
    return minimum_dist;
}*/

std::vector<std::pair<Node*, double>> Graph::findPathLengths(Node* start, int metric) {
    std::vector<std::pair<Node*, double>> distances = 
        std::vector<std::pair<Node*, double>>(nodes_.size());

    distances.push_back(std::pair<Node*, double>(start, 0));
    for (unsigned int i = 1; i < nodes_.size(); i++) {
        distances.push_back(std::pair<Node*, double>(nodes_[i], std::numeric_limits<double>::max()));
    }

    std::queue<Node*> queue;
    queue.push(start);
    while (!queue.empty()) {
        Node* front = queue.front();
        queue.pop();

        for (auto neighbor : front->getNeighbors()) {
            Edge* edge = neighbor.second;
            Node* destination = neighbor.first;

            int index = get_idx(distances, front);
            
            int val_to_add = 0;
            if (metric == 0) {
                val_to_add = edge->getFare();
            }
            else if (metric == 1) {
                val_to_add = edge->getMiles();
            }
            else if (metric == 2) {
                val_to_add = edge->getTime();
            }
            else {
                distances[0].second = -1; // metric has to be 0-2.
                return distances;
            }


            auto new_dist = val_to_add + get_seconds(distances)[index];
            
            index = get_idx(distances, destination);
            if (new_dist < get_seconds(distances)[index]) {
                distances[index].second = new_dist;
                queue.push(destination);
            }
        }
    }
    return distances;
}

double Graph::findShortestPath(Node* start, Node* end, int metric) {
    std::vector<std::pair<Node*, double>> distances = findPathLengths(start, metric);

    int index = get_idx(distances, end);
    return distances[index].second;
}


int Graph::get_idx(std::vector<std::pair<Node*, double>> distances, Node* destination) {
    std::vector<Node*> firsts;
    for (unsigned int i = 0; i < distances.size(); i++) {
        if (distances[i].first == destination) {
            return (int) i;
        }
    }
    return -1;
}

std::vector<double> Graph::get_seconds(std::vector<std::pair<Node*, double>> distances) {
    std::vector<double> seconds;
    for (unsigned int i = 0; i < distances.size(); i++) {
        seconds.push_back(distances[i].second);
    }
    return seconds;
}

std::vector<Node*> Graph::get_firsts(std::vector<std::pair<Node*, double>> distances) {
    std::vector<Node*> firsts;
    for (unsigned int i = 0; i < distances.size(); i++) {
        firsts.push_back(distances[i].first);
    }
    return firsts;
}