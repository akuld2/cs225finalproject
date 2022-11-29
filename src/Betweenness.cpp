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
    for (std::pair<Node*, Node*> p: node_pairs) {
        double relationFare = findShortestPath(p.first, p.second, 0);
        double relationTime = findShortestPath(p.first, p.second, 1);
        double relationMile = findShortestPath(p.first, p.second, 2);
        std::tuple<double, double, double> tupleRelations(relationFare, relationTime, relationMile);
        relationships_between_nodes.push_back(tupleRelations);

        double relationFare_withNode = findShortestPath_PassByNode(p.first, node, p.second, 0);
        double relationTime_withNode = findShortestPath_PassByNode(p.first, node, p.second, 1);
        double relationMile_withNode = findShortestPath_PassByNode(p.first, node, p.second, 2);
        std::tuple<double, double, double> tupleRelations_withNode(relationFare, relationTime, relationMile);
        relationships_between_nodes_passbynode.push_back(tupleRelations_withNode);
    }
}
double Graph::betweennessRatio(Node* node, int metric) {
    populateRelations(node);
    double total = 0;
    if (metric == 0) {
        for (unsigned int i = 0; i < relationships_between_nodes.size(); i++) {
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