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

      /**
       * getNode() will retrieve a reference to a node and its content.
       * @param zone the name of the zone
       * @return a pointer to a node with the matching zone
       */
      Node* getNode(std::string zone);

      unsigned int getSize();

      int minDistance(Node* first, Node* second);

      std::vector<Node*> findShortestPath(Node* start, Node* end);

  private:
      std::vector<Node*> nodes_;
};