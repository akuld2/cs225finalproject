#pragma once

#include "Node.h"
#include "Edge.h"
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

public:
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
     * getNode() will retrieve a reference to a node and its content.
     * @param zone the name of the zone
     * @return a pointer to a node with the matching zone
     */
    Node *getNode(std::string zone);

    /**
     * printGraph() will print the starting location, and then under it all of the ending zones
     */
    void printGraph() const;

    /**
     * getNode() will retrieve a reference to a node and its content.
     * @param zoneName the name of the zone
     * @return a pointer to a node with the matching zone
     */
    Node *graphIterator(std::string zoneName);

private:
    void buildGraph(std::string filename);
    std::vector<TaxiTripDetails> readCSV(std::string filename);
    std::vector<Node *> nodes_;
};