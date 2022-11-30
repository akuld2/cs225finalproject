#include "Graph.h"

double Graph::findShortestPath_PassByNode(Node* start, Node* node, Node* end, int metric) {
    std::vector<std::pair<Node*, double>> distances_part1 = findPathLengths(start, metric);
    int index_part1 = get_idx_path(distances_part1, node);
    double input1 = distances_part1[index_part1].second;

    std::vector<std::pair<Node*, double>> distances_part2 = findPathLengths(node, metric);
    int index_part2 = get_idx_path(distances_part2, end);
    double input2 = distances_part2[index_part2].second;

    return input1 + input2;
}

void Graph::combinations2(std::vector<Node*> n) {
    for(std::vector<Node*>::const_iterator it1 = n.begin(); it1 < n.end(); it1++) {
        for(std::vector<Node*>::const_iterator it2 = n.begin(); it2 < it1; it2++) {
            node_pairs.push_back(std::make_pair(*it1, *it2));
        }
    }
}

void Graph::populateRelations(Node* node) {
    combinations2(nodes_);
    // removing any pairs in node_pairs vector that contain node
    std::vector<int> list;
    for (unsigned int i = 0; i < node_pairs.size(); i++) {
        if (node_pairs[i].first == node || node_pairs[i].second == node) {
            // node_pairs.erase(node_pairs.begin()+i);
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
    relationships_between_nodes.clear();
    relationships_between_nodes_passbynode.clear();
    for (std::pair<Node*, Node*> p: node_pairs) {
        double relationFare = std::min(findShortestPath(p.first, p.second, 0),findShortestPath(p.second, p.first, 0));
        double relationTime = std::min(findShortestPath(p.first, p.second, 1),findShortestPath(p.second, p.first, 1));
        double relationMile = std::min(findShortestPath(p.first, p.second, 2),findShortestPath(p.second, p.first, 2));
        std::tuple<double, double, double> tupleRelations(relationFare, relationTime, relationMile);
        relationships_between_nodes.push_back(tupleRelations);

        double relationFare_withNode = std::min(findShortestPath_PassByNode(p.first, node, p.second, 0), findShortestPath_PassByNode(p.second, node, p.first, 0));
        double relationTime_withNode = std::min(findShortestPath_PassByNode(p.first, node, p.second, 1), findShortestPath_PassByNode(p.second, node, p.first, 1));
        double relationMile_withNode = std::min(findShortestPath_PassByNode(p.first, node, p.second, 2), findShortestPath_PassByNode(p.second, node, p.first, 2));
        std::tuple<double, double, double> tupleRelations_withNode(relationFare_withNode, relationTime_withNode, relationMile_withNode);
        relationships_between_nodes_passbynode.push_back(tupleRelations_withNode);
    }
}
double Graph::betweennessRatio(Node* node, int metric) {
    populateRelations(node);
    double total = 0;
    for (Node* n: nodes_) {
        std::cout << n->getZone() << std::endl;
    }
    if (metric == 0) {
        for (unsigned int i = 0; i < relationships_between_nodes.size(); i++) {
            std::cout << std::get<0>(relationships_between_nodes_passbynode[i]) << std::endl;
            std::cout << std::get<0>(relationships_between_nodes[i]) << std::endl;
            total += std::get<0>(relationships_between_nodes_passbynode[i]) / std::get<0>(relationships_between_nodes[i]);
        }
    } else if (metric == 1) {
        for (unsigned int i = 0; i < relationships_between_nodes.size(); i++) {
            total += std::get<1>(relationships_between_nodes_passbynode[i]) / std::get<1>(relationships_between_nodes[i]);
        }
    } else if (metric == 2) {
        for (unsigned int i = 0; i < relationships_between_nodes.size(); i++) {
            total += std::get<2>(relationships_between_nodes_passbynode[i]) / std::get<2>(relationships_between_nodes[i]);
        }
    }
    return total;
}
