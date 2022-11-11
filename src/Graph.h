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

      //metric is 0 for fare (cost), 1 for miles (length), and 2 for time
      std::vector<std::pair<Node*, double>> findPathLengths(Node* start, int metric);

      double findShortestPath(Node* start, Node* end, int metric);

  private:
      std::vector<Node*> nodes_;
};