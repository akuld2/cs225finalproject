#pragma once

#include "Edge.h"
#include <map>
#include <string>

class Node
{
public:
    Node(std::string startLocation);

    void addEdge(Node& endLocation, Edge& newEdge);
    /**
     * getNeighbors() will return an entire list of neighbors and the edge details.
     * @return a pointer to a map of nodes and edges.
     */
    std::map<Node*, Edge*> *getNeighbors();

    /**
     * getZone() will retrieve the zone name
     * @return startingLocation_
     */
    std::string getZone();

    /**
     * retrieveNeighbor() will retrieve the key of the end location
     * @return the node of the end location or empty Node if that endLocation does not exist
     */
    Node* retrieveNeighbor(Node *endLocation);

    /**
     * checkNeighborExists() will check to see if the neighbor is there
     * @param endLocation the name of the endLocation
     * @return a boolean if there is a edge
     */
    bool checkNeighborExists(std::string endLocation);

    /**
     * retrieveNeighborEdge() will retrieve the edge between the two nodes
     * @return the edge between or an empty edge if it doesn't exist
     */
    Edge *retrieveNeighborEdge(Node *endLocation);

    

private:
    std::string startingLocation_;
    std::map<Node*, Edge*> neighbors_;
};