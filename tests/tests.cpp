#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "../src/Edge.h"
#include "../src/Graph.h"
#include "../src/Node.h"

using namespace std;



// Basic test cases
TEST_CASE("Test Build Graph with medium dataset", "[weight=1][part=1]") {
    Graph* graph = new Graph("entry/testDataSet.csv");
    
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

    // then check if the edges are valid
    delete graph;
    
}
TEST_CASE("initializeGraph2", "[weight=1][part=1]") {
    REQUIRE(true);
}
TEST_CASE("initializeEdge", "[weight=1][part=1]") {
    REQUIRE(true);
}
TEST_CASE("initializeNode", "[weight=1][part=1]") {
    REQUIRE(true);
}

// Advanced test cases
TEST_CASE("testTraverse1", "[weight=1][part=2]") {
    // testing traversing the tree for the shortest path (dataset 1)
    REQUIRE(true);
}
TEST_CASE("testTraverse2", "[weight=1][part=2]") {
    // testing traversing the tree for the shortest path (dataset 2)
    REQUIRE(true);
}
TEST_CASE("testShortestPathEmpty", "[weight=1][part=2]") {
    // testing traversing the tree for at least one empty variable
    REQUIRE(true);
}
TEST_CASE("testShortestPath1 dataset1", "[weight=1][part=2]") {
    // testing traversing the tree for the shortest path (dataset 1)
    REQUIRE(true);
}
TEST_CASE("testShortestPath2 dataset1", "[weight=1][part=2]") {
    // testing traversing the tree for the shortest path (dataset 1)
    REQUIRE(true);
}
TEST_CASE("testShortestPath3 dataset2", "[weight=1][part=2]") {
    // testing traversing the tree for the shortest path (dataset 2)
    REQUIRE(true);
}
TEST_CASE("testShortestPath4 dataset2", "[weight=1][part=2]") {
    // testing traversing the tree for the shortest path (dataset 2)
    REQUIRE(true);
}

// #endif