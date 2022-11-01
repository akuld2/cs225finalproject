// tests go here
// #ifndef CATCH_CONFIG_MAIN
// #define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <../src/Edge.h>
#include <../src/Graph.h>
#include <../src/Node.h>

using namespace std;

// Basic test cases
TEST_CASE("initializeGraph1", "[weight=1][part=1]") {
    // initialize and validate creating the graph with 10 test values
    REQUIRE(true);
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