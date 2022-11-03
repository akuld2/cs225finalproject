#pragma once

#include "Edge.h"
#include <map>
#include <string>

class Node
{
  public:
      /**
       * getNeighbors() will return an entire list of neighbors and the edge details.
       * @return a pointer to a map of nodes and edges.
       */
      std::map<Node, Edge> *getNeighbors();

      /**
       * getZone() will retrieve the zone name
       * @return startingLocation_
       */
      std::string getZone();

      /**
       * retrieveNeighbor() will retrieve the key of the end location
       * @return the node of the end location or empty Node if that endLocation does not exist
       */
      Node retrieveNeighbor(Node endLocation);

      /**
       * retrieveNeighborEdge() will retrieve the edge between the two nodes
       * @return the edge between or an empty edge if it doesn't exist
       */
      Edge retrieveNeighborEdge(Node endLocation);

      /**
       * operator== deems two nodes equal if they have the same zone starting location_
       * @param zone which is the Node
      */
      bool operator==(Node zone);

private:
    std::string startingLocation_;
    std::map<Node, Edge> neighbors_;

};