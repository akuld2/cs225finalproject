// tests go here
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

Graph createGraph1() {
    // Below created 5 nodes and edges are not defined fully (eveything is in default vars) 
    // (do we need setters for the fairs, miles, and times ??)
    Node* node1 = new Node("1");
    Node* node2 = new Node("2");
    Node* node3 = new Node("3");
    Node* node4 = new Node("4");
    Node* node5 = new Node("5");
    Edge* edge1 = new Edge();
    Edge* edge2 = nullptr;
    Edge* edge3 = nullptr;
    Edge* edge4 = nullptr;
    Edge* edge5 = nullptr;
    node1->setNeighbor(node2, edge1);
    node2->setNeighbor(node3, edge2);
    node3->setNeighbor(node4, edge3);
    node4->setNeighbor(node5, edge4);
    node5->setNeighbor(node1, edge5);
    std::vector<Node*> vect;
    vect.push_back(node1);
    vect.push_back(node2);
    vect.push_back(node3);
    vect.push_back(node4);
    vect.push_back(node5);
    return Graph(vect);
}

// Basic test cases
TEST_CASE("initializeGraph1", "[weight=1][part=1]") {
    // initialize and validate creating the graph with 5 test values
    Graph graph = createGraph1();
    REQUIRE(!(graph.getNodes().empty()));
}
TEST_CASE("initializeGraph2", "[weight=1][part=1]") {
    // initialize and validate creating the graph with 20 different test values
    REQUIRE(true);
}
TEST_CASE("initializeEdge", "[weight=1][part=1]") {
    // initialize and validate creating an edge
    REQUIRE(true);
}
TEST_CASE("initializeNode", "[weight=1][part=1]") {
    // initialize and validate creating a node
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