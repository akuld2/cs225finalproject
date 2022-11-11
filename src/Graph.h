#pragma once

#include "Node.h"
#include <vector>
#include <string>
#include <algorithm>

/**
 * Graph class is our "main class" which will be a container for our graph.
 * This class will only store the nodes.
 */
class Graph
{
  public:
      /**
       * getNodes() will return an entire list of nodes.
       * @return a pointer to a vector of nodes.
       */
      Graph();

      Graph(int if_neg_1);

      Graph(std::vector<Node*> nodes);

      std::vector<Node*> getNodes();

      int get_idx(std::vector<std::pair<Node*, double>> distances, Node* destination);

      std::vector<double> get_seconds(std::vector<std::pair<Node*, double>> distances);

      std::vector<Node*> get_firsts(std::vector<std::pair<Node*, double>> distances);

      /**
       * getNode() will retrieve a reference to a node and its content.
       * @param zone the name of the zone
       * @return a pointer to a node with the matching zone
       */
      Node* getNode(std::string zone);

      unsigned int getSize();

      double minDistance(Node* first, Node* second);

      std::vector<std::pair<Node*, double>> findPathLengths(Node* start);

      double findShortestPath(Node* start, Node* end);

  private:
      std::vector<Node*> nodes_;
};