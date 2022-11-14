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

      std::vector<Node*>* getNodes();
      
      /**
       * @brief Gets the index of the node from the distances vector
       * 
       * @param distances vector of pairs
       * @param destination node that we would want the index from
       * @return index (int)
       */
      int get_idx_path(std::vector<std::pair<Node*, double>> distances, Node* destination);

      /**
       * @brief Extracts an std::vector<double> from the std::vector<std::pair<Node*, double>
       * 
       * @param distances vector of pairs
       * @return all second values in an std::vector<double>
       */
      std::vector<double> get_seconds_path(std::vector<std::pair<Node*, double>> distances);
      
      /**
       * @brief Extracts an std::vector<Node*> from the std::vector<std::pair<Node*, double>
       * 
       * @param distances vector of pairs
       * @return all first values in an std::vector<Node*>
       */
      std::vector<Node*> get_firsts_path(std::vector<std::pair<Node*, double>> distances);

      /**
       * getNode() will retrieve a reference to a node and its content.
       * @param zone the name of the zone
       * @return a pointer to a node with the matching zone
       */
      Node* getNode(std::string zone);
      
      /**
       * getSize() will return the size of the graph (number of nodes).
       * @return size of the graph
       */
      unsigned int getSize();

      /**
       * findPathLengths() will get all the path lengths with a certain node from the center.
       * @param start the start node
       * @param metric an integer specifying the data value that we want to create the minimum
       * paths with. Metric is 0 for fare (cost), 1 for miles (length), and 2 for time.
       * @return a vector of pairs of nodes and the length from the start node.
       * The length from the start node to itself is 0.
       */
      std::vector<std::pair<Node*, double>> findPathLengths(Node* start, int metric);

      /**
       * findShortestPath() uses findPathLengths() and finds the length between 2 points given a certain metric.
       * @param start the start node
       * @param end the end node
       * @param metric an integer specifying the data value that we want to create the minimum
       * paths with. Metric is 0 for fare (cost), 1 for miles (length), and 2 for time.
       * @return a vector of pairs of nodes and the length from the start node.
       * The length from the start node to itself is 0.
       */
      double findShortestPath(Node* start, Node* end, int metric);

  private:
      std::vector<Node*> nodes_;
};