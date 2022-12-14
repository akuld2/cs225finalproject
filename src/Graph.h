
#pragma once

#include "Node.h"
#include "Edge.h"
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <float.h>
#include <iostream>
#include <cfloat>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <fstream>

/**
 * Graph class is our "main class" which will be a container for our graph.
 * This class will only store the nodes.
 */
class Graph
{
public:
  struct TaxiTripDetails
  {
    double tripSecond;
    double tripMiles;
    double tripFare;
    std::string pickupLocation;
    std::string dropoffLocation;
    /**
     * Taxi constructor
     * @param second is the seconds for the trip
     * @param miles is the miles traveled for the trip
     * @param fare is the fare for the trip
     * @param pickup is the pickup location
     * @param dropoff is the dropoff location
     */
    TaxiTripDetails(double second, double miles, double fare, std::string pickup, std::string dropoff) : tripSecond(second), tripMiles(miles), tripFare(fare), pickupLocation(pickup), dropoffLocation(dropoff) {}
  };

  /**
   * this will initialize the graph by populating the nodes and edges
   * @param filename which is the name of the file
   */
  Graph(std::string filename);

  /**
   * getNodes() will return an entire list of nodes.
   * @return a pointer to a vector of nodes.
   */
  std::vector<Node *> *getNodes();

  /**
   * getNodeNames() returns an entire list of zones
   * @return std::vector<std::string> of zone names
   */
  std::vector<std::string> getNodeNames();

  Graph(std::vector<Node *> nodes);

  /**
   * getNode() will retrieve a reference to a node and its content.
   * @param zone the name of the zone
   * @return a pointer to a node with the matching zone
   */
  Node *getNode(std::string zone);

  /**
   * printGraph() will print each starting location, and then under it all of the neighboring zones
   */
  void printGraph() const;

  /**
   * printNodes() will print each zone in the graph
   */
  void printNodes() const;

  /**
   * getNode() will retrieve a reference to a node and its content.
   * @param zoneName the name of the zone
   * @return a pointer to a node with the matching zone
   */
  Node *graphIterator(std::string zoneName);

  /**
   * BFS() will return the cheapest path to go through all the nodes in a
   * connected graph.
   * @param start a pointer to the starting zone
   * @return a vector of node pointers that denotes the cheapest path
   * fare-wise
   */
  std::vector<Node *> BFS(Node *start);

  /**
   * get_idx_path() gets the index of the node from the distances vector
   * @param distances vector of pairs
   * @param destination node that we would want the index from
   * @return index (int)
   */
  int get_idx_path(std::vector<std::pair<Node *, double>> distances, Node *destination);

  /**
   * get_seconds_path() extracts an std::vector<double> from the std::vector<std::pair<Node*, double>
   * @param distances vector of pairs
   * @return all second values in an std::vector<double>
   */
  std::vector<double> get_seconds_path(std::vector<std::pair<Node *, double>> distances);

  /**
   * @brief Extracts an std::vector<Node*> from the std::vector<std::pair<Node*, double>
   *
   * @param distances vector of pairs
   * @return all first values in an std::vector<Node*>
   */
  std::vector<Node *> get_firsts_path(std::vector<std::pair<Node *, double>> distances);

  /**
   * getSize() will return the size of the graph (number of nodes).
   * @return size of the graph
   */
  unsigned int getSize();

  /**
   * Dijkstra method
   * findPathLengths() will get all the path lengths from start to any other node.
   * @param start the start node
   * @param metric an integer specifying the data value that we want to create the minimum
   * paths with. Metric is 0 for fare (cost), 1 for time, and 2 for miles (length)
   * @return a vector of pairs of nodes and the length from the start node.
   * The length from the start node to itself is 0.
   */
  std::vector<std::pair<Node *, double>> findPathLengths(Node *start, int metric);

  /**
   * Dijkstra method
   * getShortestPath() returns a std::vector<Node*> that is the path of nodes from the start node to the end
   * @param distances
   * @return std::vector<Node*> that is the path of nodes from the start node to the end
   */
  std::vector<Node*> getShortestPath(Node *start, Node *end, int metric);

  /**
   * Dijkstra method
   * findShortestPath() uses findPathLengths() and finds the length between 2 points given a certain metric.
   * @param start the start node
   * @param end the end node
   * @param metric an integer specifying the data value that we want to create the minimum
   * paths with. Metric is 0 for fare (cost), 1 for time, and 2 for miles (length)
   * @return the length from the start node to end node
   * The length from the start node to itself is 0.
   */
  double findShortestPath(Node *start, Node *end, int metric);

  /**
   * Betweenness Centrality method
   * findScoreByNode() uses findShortestPath() and determines the score of the relationships 
   * that pass by node given a certain metric
   * @param start the start node
   * @param node the node that is to be centered between start and end nodes for betweenness
   * @param end the end node
   * @param metric Metric is 0 for fare (cost), 1 for time, and 2 for miles (length)
   * @return int the score of the two nodes' relationship
   */
  int findScoreByNode(Node *start, Node *node, Node *end, int metric);

  /**
   * Betweenness Centrality method
   * allPairs() finds all combinations or all pairs of nodes in the graph excluding the Node node
   * sets the private variable called node_pairs
   * @param std::vector<int> n total number of nodes in the graph
   */
  void allPairs(std::vector<Node *> n);

  /**
   * Betweenness Centrality method
   * switchingABforMin() uses findShortestPath() and findShortestPathPassByNode()
   * and compares their values for the min and returns a pair with an adjucted starting and ending nodes
   * @param a Node a
   * @param b Node b
   * @param metric Metric is 0 for fare (cost), 1 for time, and 2 for miles (length)
   * @return std::pair<Node*, Node*> 
   */
  std::pair<Node*, Node*> switchingABforMin(Node *a, Node *b, int metric);

  /**
   * Betweenness Centrality method
   * populateRelations() uses node_pairs to populate
   * relationships_between_nodes and relationships_between_nodes_passbynode
   * @param node that is to be centered between start and end nodes for betweenness
   */
  void populateRelations(Node *node);

  /**
   * Betweenness Centrality method
   * betweennessRatio() uses relationships to calculate each individual ratio
   * and returns their sum
   * @param node that is to be centered between start and end nodes for betweenness
   * @param int metric an integer specifying the data value that we want to create the minimum
   * paths with. Metric is 0 for fare (cost), 1 for time, and 2 for miles (length)
   * @return double the sum of individual relationships and realtionshipsPassByNode
   */
  double betweennessRatio(Node *node, int metric);

  /**
   * Betweenness Centrality method
   * betweennessCentrality() uses the passed in metric to determine the busiest route or the central hub
   * given fare, time or mile
   * @param int metric an integer specifying the data value that we want to create the minimum
   * paths with. Metric is 0 for fare (cost), 1 for time, and 2 for miles (length)
   * @return std::string Node that is the busiest route given the metric
   */
  std::string betweennessCentrality(int metric);

private:
  /**
   * buildGraph() is a helper function to build a graph from a CSV file.
   * @param filename the name of the csv datafile you are using in a string
   */
  void buildGraph(std::string filename);

  /**
   * readCSV() is a helper function to read data from a CSV file.
   * @param filename the name of the csv datafile you are using in a string
   * @return a vector filled with the relevant data from each entry in the file
   */
  std::vector<TaxiTripDetails> readCSV(std::string filename);

  /**
   * visited() checks if the node pointer node is in the vector passed
   * to the function.
   * @param node the node to search for
   * @param vec the vector to search in
   * @return if the node is in the vector
   */
  bool visited(Node *node, std::vector<Node *> vec);

  std::vector<Node *> nodes_;
  // private variables for the betweeness centrality algo
  std::vector<std::pair<Node *, Node *>> node_pairs;
  // relationships between nodes
  std::vector<std::tuple<double, double, double>> relationships;
  std::vector<std::tuple<double, double, double>> relationshipsPassbynode;
};
