#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include "../src/Edge.h"
#include "../src/Graph.h"
#include "../src/Node.h"

using namespace std;

// Basic test cases
TEST_CASE("Test Build Graph with medium dataset", "[part=1]")
{
    Graph *graph = new Graph("datasets/mediumBasic.csv");

    // first check if all of the nodes are there
    REQUIRE(graph->getNode("7") != NULL);
    REQUIRE(graph->getNode("24") != NULL);
    REQUIRE(graph->getNode("3") != NULL);
    REQUIRE(graph->getNode("8") != NULL);
    REQUIRE(graph->getNode("56") != NULL);
    REQUIRE(graph->getNode("32") != NULL);
    REQUIRE(graph->getNode("43") != NULL);

    // then check all of the neighbors
    REQUIRE(graph->getNode("7")->checkNeighborExists("24") == true);
    REQUIRE(graph->getNode("24")->checkNeighborExists("3") == true);
    REQUIRE(graph->getNode("3")->checkNeighborExists("8") == true);
    REQUIRE(graph->getNode("8")->checkNeighborExists("24") == true);
    REQUIRE(graph->getNode("8")->checkNeighborExists("56") == true);
    REQUIRE(graph->getNode("8")->checkNeighborExists("7") == true);
    REQUIRE(graph->getNode("56")->checkNeighborExists("43") == true);
    REQUIRE(graph->getNode("56")->checkNeighborExists("3") == true);
    REQUIRE(graph->getNode("56")->checkNeighborExists("32") == true);
    REQUIRE(graph->getNode("32")->checkNeighborExists("43") == true);
    REQUIRE(graph->getNode("32")->checkNeighborExists("3") == true);
    REQUIRE(graph->getNode("43")->checkNeighborExists("7") == true);
    REQUIRE(graph->getNode("43")->checkNeighborExists("8") == true);

    // check to see if it is a directed graph by going the oppsite
    REQUIRE(graph->getNode("24")->checkNeighborExists("7") == false);
    REQUIRE(graph->getNode("3")->checkNeighborExists("24") == false);
    REQUIRE(graph->getNode("8")->checkNeighborExists("3") == false);
    REQUIRE(graph->getNode("24")->checkNeighborExists("8") == false);
    REQUIRE(graph->getNode("56")->checkNeighborExists("8") == false);
    REQUIRE(graph->getNode("7")->checkNeighborExists("8") == false);
    REQUIRE(graph->getNode("43")->checkNeighborExists("56") == false);
    REQUIRE(graph->getNode("3")->checkNeighborExists("56") == false);
    REQUIRE(graph->getNode("32")->checkNeighborExists("56") == false);
    REQUIRE(graph->getNode("43")->checkNeighborExists("32") == false);
    REQUIRE(graph->getNode("3")->checkNeighborExists("32") == false);
    REQUIRE(graph->getNode("7")->checkNeighborExists("43") == false);
    REQUIRE(graph->getNode("8")->checkNeighborExists("43") == false);

    // then check if the edges have the valid values
    REQUIRE(graph->getNode("7")->retrieveNeighborEdgeData("24") == std::vector<double>{24.00, 1345, 8.44});
    REQUIRE(graph->getNode("24")->retrieveNeighborEdgeData("3") == std::vector<double>{15, 1101, 9.1});
    REQUIRE(graph->getNode("3")->retrieveNeighborEdgeData("8") == std::vector<double>{17, 685, 8.5});
    REQUIRE(graph->getNode("8")->retrieveNeighborEdgeData("24") == std::vector<double>{9, 1256, 2.23});
    REQUIRE(graph->getNode("8")->retrieveNeighborEdgeData("56") == std::vector<double>{5, 1800, 4});
    REQUIRE(graph->getNode("8")->retrieveNeighborEdgeData("7") == std::vector<double>{113.00, 693, 1.5});
    REQUIRE(graph->getNode("56")->retrieveNeighborEdgeData("43") == std::vector<double>{6.00, 660, 3});
    REQUIRE(graph->getNode("56")->retrieveNeighborEdgeData("3") == std::vector<double>{11.00,829,3.79});
    REQUIRE(graph->getNode("56")->retrieveNeighborEdgeData("32") == std::vector<double>{3.00,357,16.75});
    REQUIRE(graph->getNode("32")->retrieveNeighborEdgeData("43") == std::vector<double>{10.00,762,0.3});
    REQUIRE(graph->getNode("32")->retrieveNeighborEdgeData("3") == std::vector<double>{30.00,357,16.75});
    REQUIRE(graph->getNode("43")->retrieveNeighborEdgeData("7") == std::vector<double>{3.25,1201,0.15});
    REQUIRE(graph->getNode("43")->retrieveNeighborEdgeData("8") == std::vector<double>{12,940,1.95});
    delete graph;
}
TEST_CASE("initializeGraph2", "[weight=1][part=1]")
{
    REQUIRE(true);
}
TEST_CASE("initializeEdge", "[weight=1][part=1]")
{
    REQUIRE(true);
}
TEST_CASE("initializeNode", "[weight=1][part=1]")
{
    REQUIRE(true);
}

// Advanced test cases
TEST_CASE("testTraverse1", "[weight=1][part=2]")
{
    // testing traversing the tree for the shortest path (dataset 1)
    REQUIRE(true);
}
TEST_CASE("testTraverse2", "[weight=1][part=2]")
{
    // testing traversing the tree for the shortest path (dataset 2)
    REQUIRE(true);
}
TEST_CASE("testShortestPathEmpty", "[weight=1][part=2]")
{
    // testing traversing the tree for at least one empty variable
    REQUIRE(true);
}
TEST_CASE("testShortestPath1 dataset1", "[weight=1][part=2]")
{
    // testing traversing the tree for the shortest path (dataset 1)
    REQUIRE(true);
}
TEST_CASE("testShortestPath2 dataset1", "[weight=1][part=2]")
{
    // testing traversing the tree for the shortest path (dataset 1)
    REQUIRE(true);
}
TEST_CASE("testShortestPath3 dataset2", "[weight=1][part=2]")
{
    // testing traversing the tree for the shortest path (dataset 2)
    REQUIRE(true);
}
TEST_CASE("testShortestPath4 dataset2", "[weight=1][part=2]")
{
    // testing traversing the tree for the shortest path (dataset 2)
    REQUIRE(true);
}

// #endif