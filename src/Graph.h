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
    std::vector<Node*>* getNodes();

    std::vector<std::string> getNodeNames();

    Graph(std::vector<Node*> nodes);
      
    /**
     * getNode() will retrieve a reference to a node and its content.
     * @param zone the name of the zone
     * @return a pointer to a node with the matching zone
     */
    Node* getNode(std::string zone);

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
    std::vector<Node*> BFS(Node* start);

      
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
     * getSize() will return the size of the graph (number of nodes).
     * @return size of the graph
     */
    unsigned int getSize();

    /**
     * findPathLengths() will get all the path lengths with a certain node from the center.
     * @param start the start node
     * @param metric an integer specifying the data value that we want to create the minimum
     * paths with. Metric is 0 for fare (cost), 1 for time, and 2 for miles (length)
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
     * @return the length from the start node to end node
     * The length from the start node to itself is 0.
     */
    double findShortestPath(Node* start, Node* end, int metric);

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
    bool visited(Node* node, std::vector<Node*> vec);
    
    std::vector<Node*> nodes_;    
};