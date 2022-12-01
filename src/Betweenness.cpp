#include "Graph.h"

double Graph::findShortestPathPassByNode(Node* start, Node* node, Node* end, int metric) {
    std::vector<std::pair<Node*, double>> distances_part1 = findPathLengths(start, metric);
    int index_part1 = get_idx_path(distances_part1, node);
    double input1 = distances_part1[index_part1].second;

    std::vector<std::pair<Node*, double>> distances_part2 = findPathLengths(node, metric);
    int index_part2 = get_idx_path(distances_part2, end);
    double input2 = distances_part2[index_part2].second;

    return input1 + input2;
}

void Graph::allPairs(std::vector<Node*> n) {
    for(std::vector<Node*>::const_iterator it1 = n.begin(); it1 < n.end(); it1++) {
        for(std::vector<Node*>::const_iterator it2 = n.begin(); it2 < it1; it2++) {
            node_pairs.push_back(std::make_pair(*it1, *it2));
        }
    }
}

void Graph::populateRelations(Node* node) {
    allPairs(nodes_);
    // removing any pairs in node_pairs vector that contain node
    std::vector<int> list;
    for (unsigned int i = 0; i < node_pairs.size(); i++) {
        if (node_pairs[i].first == node || node_pairs[i].second == node) {
            list.push_back(i);
        }
    }
    std::vector<std::pair<Node*, Node*>> newNodePairs;
    unsigned int idx = 0;
    for (unsigned int i = 0; i < node_pairs.size(); i++) {
        if (!list.empty()) {
            if ((int) i != list[idx]) {
                newNodePairs.push_back(node_pairs[i]);
            } else {
                idx++;
            }
        } else {
            return;
        }
    }
    node_pairs = newNodePairs;
    relationships.clear();
    relationshipsPassbynode.clear();
    for (std::pair<Node*, Node*> p: node_pairs) {
        double relationFare = std::min(findShortestPath(p.first, p.second, 0),findShortestPath(p.second, p.first, 0));
        double relationTime = std::min(findShortestPath(p.first, p.second, 1),findShortestPath(p.second, p.first, 1));
        double relationMile = std::min(findShortestPath(p.first, p.second, 2),findShortestPath(p.second, p.first, 2));
        std::tuple<double, double, double> tupleRelations(relationFare, relationTime, relationMile);
        relationships.push_back(tupleRelations);

        double relationFareNode = std::min(findShortestPathPassByNode(p.first, node, p.second, 0), findShortestPathPassByNode(p.second, node, p.first, 0));
        double relationTimeNode = std::min(findShortestPathPassByNode(p.first, node, p.second, 1), findShortestPathPassByNode(p.second, node, p.first, 1));
        double relationMileNode = std::min(findShortestPathPassByNode(p.first, node, p.second, 2), findShortestPathPassByNode(p.second, node, p.first, 2));
        std::tuple<double, double, double> tupleRelationsNode(relationFareNode, relationTimeNode, relationMileNode);
        relationshipsPassbynode.push_back(tupleRelationsNode);
    }
}
double Graph::betweennessRatio(Node* node, int metric) {
    populateRelations(node);
    double total = 0;
    if (metric == 0) {
        for (unsigned int i = 0; i < relationships.size(); i++) {
            total += std::get<0>(relationshipsPassbynode[i]) / std::get<0>(relationships[i]);
        }
    } else if (metric == 1) {
        for (unsigned int i = 0; i < relationships.size(); i++) {
            total += std::get<1>(relationshipsPassbynode[i]) / std::get<1>(relationships[i]);
        }
    } else if (metric == 2) {
        for (unsigned int i = 0; i < relationships.size(); i++) {
            total += std::get<2>(relationshipsPassbynode[i]) / std::get<2>(relationships[i]);
        }
    }
    return total;
}
