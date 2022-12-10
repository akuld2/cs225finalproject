#include "Graph.h"

int Graph::findScoreByNode(Node* start, Node* node, Node* end, int metric) {

    double input1 = findShortestPath(start, node, metric);
    double input2 = findShortestPath(node, end, metric);   

    double total = input1 + input2;
    int out = 0;
    double distancesWithoutNode = findShortestPath(start, end, metric);

    if (distancesWithoutNode >= total) {
        out = 1;
    }

    return out;
}

void Graph::allPairs(std::vector<Node*> n) {
    for (unsigned int i = 0; i < n.size(); i++) {
        for (unsigned int j = 0; j < n.size(); j++) {
            if (i != j) {
                node_pairs.push_back(std::make_pair(n[i], n[j]));
            }
        }
    }
    for(auto& p : node_pairs){
        if (std::stoi(p.first->getZone()) < std::stoi(p.second->getZone())) {
            Node* tmp = p.first;
            p.first = p.second;
            p.second = tmp;
        }
    }
    std::sort(node_pairs.begin(), node_pairs.end());
    node_pairs.erase(std::unique(node_pairs.begin(), node_pairs.end()), node_pairs.end());
}

void Graph::populateRelations(Node* node) {
    allPairs(nodes_);

    // removing any pairs in node_pairs vector that contain the node
    std::vector<std::pair<Node *, Node *>> newNodePairs;
    for (unsigned int i = 0; i < node_pairs.size(); i++) {
        if (node_pairs[i].first != node && node_pairs[i].second != node) {
            newNodePairs.push_back(node_pairs[i]);
        }
    }
    node_pairs = newNodePairs;

    relationships.clear();
    relationshipsPassbynode.clear();
    for (std::pair<Node*, Node*>& p: node_pairs) {
        std::tuple<int, int, int> tupleRelations(1, 1, 1);
        relationships.push_back(tupleRelations);

        std::pair<Node*, Node*> new_pFare = switchingABforMin(p.first, p.second, 0);
        std::pair<Node*, Node*> new_pTime = switchingABforMin(p.first, p.second, 1);
        std::pair<Node*, Node*> new_pMile = switchingABforMin(p.first, p.second, 2);
        int fareNodeScore = findScoreByNode(new_pFare.first, node, new_pFare.second, 0);
        int timeNodeScore = findScoreByNode(new_pTime.first, node, new_pTime.second, 1);
        int mileNodeScore = findScoreByNode(new_pMile.first, node, new_pMile.second, 2);
        std::tuple<int, int, int> tupleRelationsNode(fareNodeScore, timeNodeScore, mileNodeScore);
        relationshipsPassbynode.push_back(tupleRelationsNode);
    }
}
std::pair<Node*, Node*> Graph::switchingABforMin(Node* a, Node* b, int metric) {
    // std::cout << "switchingABforMin()" << std::endl;
    double aRel = findShortestPath(a, b, metric);
    double bRel = findShortestPath(b, a, metric);
    std::pair<Node*, Node*> switchedPair;
    if (aRel > bRel) {
        switchedPair = std::make_pair(b, a);
    } else {
        switchedPair = std::make_pair(a, b);
    }
    return switchedPair;
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

std::string Graph::betweennessCentrality(int metric) {
    std::vector<double> busiestRoute;
    std::map<double, std::string> centralityMap;
    if (metric == 0) {
        for (unsigned int i = 0; i < nodes_.size(); i++) {
            double total = betweennessRatio(nodes_[i], 0);
            std::string zone = nodes_[i]->getZone();
            centralityMap.insert(std::make_pair(total, zone));
            busiestRoute.push_back(total);
        }
    } else if (metric == 1) {
        for (unsigned int i = 0; i < nodes_.size(); i++) {
            double total = betweennessRatio(nodes_[i], 1);
            std::string zone = nodes_[i]->getZone();
            centralityMap.insert(std::make_pair(total, zone));
            busiestRoute.push_back(total);
        }
    } else if (metric == 2) {
        for (unsigned int i = 0; i < nodes_.size(); i++) {
            double total = betweennessRatio(nodes_[i], 2);
            std::string zone = nodes_[i]->getZone();
            centralityMap.insert(std::make_pair(total, zone));
            busiestRoute.push_back(total);
        }
    }
    double max = busiestRoute[0];
    for (unsigned i = 0; i < busiestRoute.size(); i++) {
        if (max < busiestRoute[i]) {
            max = busiestRoute[i];
        }
    }
    return centralityMap[max];
}
