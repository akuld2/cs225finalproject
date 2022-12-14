#include "Graph.h"


std::vector<std::pair<Node*, double>> Graph::findPathLengths(Node* start, int metric) {
    std::vector<std::pair<Node*, double>> distances = 
        std::vector<std::pair<Node*, double>>(nodes_.size());

    distances.push_back(std::pair<Node*, double>(start, 0.0));
    for (unsigned int i = 0; i < nodes_.size(); i++) {
        if (nodes_[i] != start) {
            distances.push_back(std::pair<Node*, double>(nodes_[i], DBL_MAX));
        }
    }

    std::queue<Node*> queue;
    queue.push(start);

    start->prev = nullptr;

    while (!queue.empty()) {
        Node* front = queue.front();
        queue.pop();

        for (auto neighbor : *(front->getNeighbors())) {
            Edge* edge = neighbor.second;
            Node* destination = neighbor.first;

            int index = get_idx_path(distances, front);
            
            double val_to_add;
            if (metric == 0) {
                val_to_add = edge->getFare();
            }
            else if (metric == 1) {
                val_to_add = edge->getTime();
            }
            else if (metric == 2) {
                val_to_add = edge->getMiles();
            }
            else {
                distances[0].second = -1.0; // metric has to be 0-2.
                return distances;
            }


            double new_dist = val_to_add + get_seconds_path(distances)[index];

            
            index = get_idx_path(distances, destination);

            if (new_dist < get_seconds_path(distances)[index]) {
                destination->prev = front;
                distances[index].second = new_dist;
                queue.push(destination);
            }
        }
    }
    return distances;
}

double Graph::findShortestPath(Node* start, Node* end, int metric) {
    std::vector<std::pair<Node*, double>> distances = findPathLengths(start, metric);

    int index = get_idx_path(distances, end);
    return distances[index].second;
}

std::vector<Node*> Graph::getShortestPath(Node* start, Node* end, int metric) {
    std::vector<std::pair<Node*, double>> distances = findPathLengths(start, metric);
    Node* curr = end;
    std::vector<Node*> path;

    while (curr != start) {
        path.push_back(curr);
        curr = curr->prev;
    }

    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}

int Graph::get_idx_path(std::vector<std::pair<Node*, double>> distances, Node* destination) {
    std::vector<Node*> firsts;
    for (unsigned int i = 0; i < distances.size(); i++) {
        if (distances[i].first == destination) {
            return (int) i;
        }
    }
    return -1;
}

std::vector<double> Graph::get_seconds_path(std::vector<std::pair<Node*, double>> distances) {
    std::vector<double> seconds;
    for (unsigned int i = 0; i < distances.size(); i++) {
        seconds.push_back(distances[i].second);
    }
    return seconds;
}
std::vector<Node*> Graph::get_firsts_path(std::vector<std::pair<Node*, double>> distances) {
    std::vector<Node*> firsts;
    for (unsigned int i = 0; i < distances.size(); i++) {
        firsts.push_back(distances[i].first);
    }
    return firsts;
}