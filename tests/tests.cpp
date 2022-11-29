// tests go here
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


// Old Dijkstra tests
Graph prelimTestCase() {
    // Below created 5 nodes and edges are not defined fully (eveything is in default vars) 
    // (do we need setters for the fairs, miles, and times ??)
    Node* node1 = new Node("1");
    Node* node2 = new Node("2");
    Node* node3 = new Node("3");
    Node* node4 = new Node("4");
    Node* node5 = new Node("5");
    Edge* edge1 = new Edge(1.0, 1.0, 1.0);
    Edge* edge2 = new Edge(2.0, 2.0, 2.0);
    Edge* edge3 = new Edge(3.0, 3.0, 3.0);
    Edge* edge4 = new Edge(4.0, 4.0, 4.0);
    Edge* edge5 = new Edge(5.0, 5.0, 5.0);
    node1->setNeighbor(node2, edge1);
    node1->setNeighbor(node5, edge5);
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

TEST_CASE("Test Find Path Lengths", "[weight=1][part=2]") {
    Graph graph = prelimTestCase();
    REQUIRE(!(graph.getNodes()->empty()));
    REQUIRE(graph.getNode("1") != nullptr);
    REQUIRE(graph.getNode("2") != nullptr);
    auto distances = graph.findPathLengths(graph.getNode("1"), 1);
    REQUIRE(!distances.empty());

    REQUIRE(graph.findShortestPath(graph.getNode("1"), graph.getNode("2"), 1) == 1.0);
    REQUIRE(graph.findShortestPath(graph.getNode("1"), graph.getNode("3"), 1) == 3.0);
    REQUIRE(graph.findShortestPath(graph.getNode("1"), graph.getNode("4"), 1) == 6.0);
    REQUIRE(graph.findShortestPath(graph.getNode("1"), graph.getNode("5"), 1) == 5.0);
}

TEST_CASE("Dijkstra initialize", "[weight=1][part=2]") {
    Graph* graph = new Graph("datasets/smallBasic.csv");
    REQUIRE(!(graph->getNodes()->empty()));
    REQUIRE(graph->getNode("1") != nullptr);
    REQUIRE(graph->getNode("2") != nullptr);
    REQUIRE(graph->getNode("3") != nullptr);

    auto distances = graph->findPathLengths(graph->getNode("1"), 0);
    REQUIRE(!distances.empty());
}

// Metric is 0 for fare (cost), 1 for time, and 2 for miles (length)
TEST_CASE("Dijkstra small basic test", "[weight=1][part=2]") {
    Graph* graph = new Graph("datasets/smallBasic.csv");

    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("1"), 0) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("2"), 0) == 3.50);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("3"), 0) == 5.75);

    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("1"), 0) == 14.0);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("2"), 0) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("3"), 0) == 2.25);

    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("1"), 0) == 11.75);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("2"), 0) == 15.25);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("3"), 0) == 0.0); 


    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("1"), 1) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("2"), 1) == 456.0);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("3"), 1) == 1245.0);

    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("1"), 1) == 1900.0);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("2"), 1) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("3"), 1) == 789.0);

    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("1"), 1) == 1111.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("2"), 1) == 1567.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("3"), 1) == 0.0);


    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("1"), 2) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("2"), 2) == 2.2);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("3"), 2) == 2.6);

    // This test is different due to floating point imprecision. All tests should be updated to be this
    REQUIRE(std::abs(graph->findShortestPath(graph->getNode("2"), graph->getNode("1"), 2) - 6.1) < 0.001);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("2"), 2) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("3"), 2) == 0.4);

    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("1"), 2) == 5.7);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("2"), 2) == 7.9);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("3"), 2) == 0.0);

    delete graph;
}

// Metric is 0 for fare (cost), 1 for time, and 2 for miles (length)
TEST_CASE("Dijkstra small complex test", "[weight=1][part=2]")
{
    Graph* graph = new Graph("datasets/smallComplex.csv");

    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("1"), 0) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("2"), 0) == 3.50);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("3"), 0) == 5.75);

    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("1"), 0) == 2.70);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("2"), 0) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("3"), 0) == 2.25);

    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("1"), 0) == 5.85);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("2"), 0) == 3.15);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("3"), 0) == 0.0); 


    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("1"), 1) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("2"), 1) == 456.0);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("3"), 1) == 1210.0); 

    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("1"), 1) == 463.0);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("2"), 1) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("3"), 1) == 789.0);

    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("1"), 1) == 1111.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("2"), 1) == 823.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("3"), 1) == 0.0);


    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("1"), 2) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("2"), 2) == 2.22);
    REQUIRE(graph->findShortestPath(graph->getNode("1"), graph->getNode("3"), 2) == 2.62);

    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("1"), 2) == 3.1);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("2"), 2) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("2"), graph->getNode("3"), 2) == 0.4);

    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("1"), 2) == 3.7);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("2"), 2) == 0.6);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("3"), 2) == 0.0);

    delete graph;
}

TEST_CASE("Dijkstra medium complex test", "[weight=1][part=2]")
{
    Graph* graph = new Graph("datasets/mediumComplex.csv");

    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("3"), 0) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("32"), 0) == 13.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("56"), 0) == 10.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("8"), 0) == 16.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("24"), 0) == 14.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("43"), 0) == 16.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("7"), 0) == 19.25);

    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("3"), 0) == 13.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("32"), 0) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("56"), 0) == 2.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("8"), 0) == 8.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("24"), 0) == 17.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("43"), 0) == 8.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("7"), 0) == 11.25);

    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("3"), 0) == 11.0);
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("32"), 0) == 3.0);
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("56"), 0) == 0.0); 
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("8"), 0) == 6.0);
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("24"), 0) == 15.0);
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("43"), 0) == 6.0); 
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("7"), 0) == 9.25);

    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("3"), 0) == 16.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("32"), 0) == 8.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("56"), 0) == 5.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("8"), 0) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("24"), 0) == 9.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("43"), 0) == 11.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("7"), 0) == 14.25);

    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("3"), 0) == 22.25);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("32"), 0) == 13.25);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("56"), 0) == 11.25);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("8"), 0) == 17.25);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("24"), 0) == 24.0);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("43"), 0) == 4.25);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("7"), 0) == 0.0);

    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("3"), 0) == 18.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("32"), 0) == 9.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("56"), 0) == 7.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("8"), 0) == 13.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("24"), 0) == 22.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("43"), 0) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("7"), 0) == 3.25);

    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("3"), 0) == 15.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("32"), 0) == 16.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("56"), 0) == 13.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("8"), 0) == 8.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("24"), 0) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("43"), 0) == 19.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("7"), 0) == 22.25);

    // time!
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("3"), 1) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("32"), 1) == 356.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("56"), 1) == 712.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("8"), 1) == 685.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("24"), 1) == 1100.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("43"), 1) == 1118.0);
    REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("7"), 1) == 1378.0);

    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("3"), 1) == 357.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("32"), 1) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("56"), 1) == 356.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("8"), 1) == 1042.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("24"), 1) == 1457.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("43"), 1) == 762.0);
    REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("7"), 1) == 1735.0);

    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("3"), 1) == 714.0);
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("32"), 1) == 357.0);
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("56"), 1) == 0.0); 
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("8"), 1) == 1399.0);
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("24"), 1) == 1814.0);
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("43"), 1) == 660.0); 
    REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("7"), 1) == 1861.0);

    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("3"), 1) == 684.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("32"), 1) == 1040.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("56"), 1) == 1396.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("8"), 1) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("24"), 1) == 1256.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("43"), 1) == 945.0);
    REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("7"), 1) == 693.0);

    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("3"), 1) == 1378.0);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("32"), 1) == 1734.0);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("56"), 1) == 1859.0);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("8"), 1) == 694.0);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("24"), 1) == 1345.0);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("43"), 1) == 1200.0);
    REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("7"), 1) == 0.0);

    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("3"), 1) == 1120.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("32"), 1) == 763.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("56"), 1) == 659.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("8"), 1) == 946.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("24"), 1) == 2202.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("43"), 1) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("7"), 1) == 1201);

    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("3"), 1) == 1101.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("32"), 1) == 1457.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("56"), 1) == 1813.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("8"), 1) == 1255.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("24"), 1) == 0.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("43"), 1) == 2200.0);
    REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("7"), 1) == 1344.0);

    // // miles (passes)
    // REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("3"), 2) == 0.0);
    // // REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("32"), 2) == 7.39);
    // REQUIRE(std::abs(graph->findShortestPath(graph->getNode("3"), graph->getNode("32"), 2) - 7.39) < 0.001);
    // REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("56"), 2) == 3.89);
    // REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("8"), 2) == 6.89);
    // REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("24"), 2) == 9.12);
    // REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("43"), 2) == 6.89);
    // REQUIRE(graph->findShortestPath(graph->getNode("3"), graph->getNode("7"), 2) == 8.39);

    // REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("3"), 2) == 7.04);
    // REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("32"), 2) == 0.0);
    // REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("56"), 2) == 3.25);
    // REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("8"), 2) == 2.25);
    // REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("24"), 2) == 4.48);
    // REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("43"), 2) == 0.3);
    // REQUIRE(graph->findShortestPath(graph->getNode("32"), graph->getNode("7"), 2) == 0.45);

    // REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("3"), 2) == 3.79);
    // REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("32"), 2) == 3.5);
    // REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("56"), 2) == 0.0); 
    // REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("8"), 2) == 3.0);
    // REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("24"), 2) == 5.23);
    // REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("43"), 2) == 3.0); 
    // REQUIRE(graph->findShortestPath(graph->getNode("56"), graph->getNode("7"), 2) == 3.15);

    // REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("3"), 2) == 7.89);
    // REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("32"), 2) == 6.9);
    // REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("56"), 2) == 4.0);
    // REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("8"), 2) == 0.0);
    // REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("24"), 2) == 2.23);
    // REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("43"), 2) == 2.15);
    // REQUIRE(graph->findShortestPath(graph->getNode("8"), graph->getNode("7"), 2) == 1.5);

    // REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("3"), 2) == 9.49);
    // REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("32"), 2) == 0.95);
    // REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("56"), 2) == 3.4);
    // REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("8"), 2) == 1.7);
    // REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("24"), 2) == 3.93);
    // REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("43"), 2) == 0.45);
    // REQUIRE(graph->findShortestPath(graph->getNode("7"), graph->getNode("7"), 2) == 0.0);

    // REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("3"), 2) == 6.74);
    // REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("32"), 2) == 0.5);
    // REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("56"), 2) == 2.95);
    // REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("8"), 2) == 1.95);
    // REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("24"), 2) == 4.18);
    // REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("43"), 2) == 0.0);
    // REQUIRE(graph->findShortestPath(graph->getNode("43"), graph->getNode("7"), 2) == 0.15);

    // REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("3"), 2) == 9.1);
    // REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("32"), 2) == 4.78);
    // REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("56"), 2) == 6.13);
    // REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("8"), 2) == 2.13);
    // REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("24"), 2) == 0.0);
    // REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("43"), 2) == 4.28);
    // REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("7"), 2) == 3.63);

    delete graph;
}

// TEST_CASE("Betweenness Multiple Edges test", "[weight=1][part=2]")
// {
//     Graph* graph = new Graph("datasets/multipleEdges.csv");

//     REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("35"), 0) == 18.0);
//     REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("35"), 1) == 15.0);
//     REQUIRE(graph->findShortestPath(graph->getNode("24"), graph->getNode("35"), 2) == 5.25);

//     delete graph;
// }

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
TEST_CASE("test averaging the edges", "[weight=1][part=1]")
{
    Graph *graph = new Graph("datasets/multipleEdges.csv");
    REQUIRE(graph->getNode("24")->retrieveNeighborEdgeData("35") == std::vector<double>{18,15,5.25});
    delete graph;
    
}
TEST_CASE("test if bad data is inputted", "[weight=1][part=1]")
{
    Graph *graph = new Graph("datasets/missingValues.csv");
    REQUIRE(graph->getNode("89") != NULL);
    REQUIRE(graph->getNode("91") != NULL);
    REQUIRE(graph->getNode("90") != NULL);
    REQUIRE(graph->getNode("88") != NULL);
    REQUIRE(graph->getNode("96") != NULL);
    REQUIRE(graph->getNode("86") == NULL);
    REQUIRE(graph->getNode("87") == NULL);
    REQUIRE(graph->getNode("85") == NULL);
    delete graph;
}

// TEST_CASE("initializeNode", "[weight=1][part=1]")
// {
//     REQUIRE(true);
// }

// Advanced test cases
TEST_CASE("test cheapest path small", "[weight=1][part=2]")
{
    // testing traversing the tree for the cheapest path (dataset smallBasic)
    Graph *graph = new Graph("datasets/smallBasic.csv");
    std::vector<Node*> path = graph->BFS(graph->getNodes()->at(0)); // first node is 1

    std::string ss = "";
    for (unsigned i = 0; i < path.size(); i++) {
        ss += path.at(i)->getZone() + " ";
    }
    REQUIRE(ss == "1 2 3 ");

    delete graph;
}

TEST_CASE("test cheapest path medium", "[weight=1][part=2]")
{
    // testing traversing the tree for the cheapest path (dataset mediumBasic)
    Graph *graph = new Graph("datasets/mediumBasic.csv");
    std::vector<Node*> path = graph->BFS(graph->getNodes()->at(0)); // first node is 7

    std::string ss = "";
    for (unsigned i = 0; i < path.size(); i++) {
        ss += path.at(i)->getZone() + " ";
    }
    REQUIRE(ss == "7 24 3 8 56 32 43 ");

    delete graph;
}

TEST_CASE("test cheapest path large", "[weight=1][part=2]")
{
    // testing traversing the tree for the cheapest path (dataset hardBasic)
    Graph *graph = new Graph("datasets/hardBasic.csv");
    std::vector<Node*> path = graph->BFS(graph->getNodes()->at(0)); // first node is 3

    std::string ss = "";
    for (unsigned i = 0; i < path.size(); i++) {
        ss += path.at(i)->getZone() + " ";
    }
    // The expected cheapest path... "3 8 56 32 43 7 24 96 95 90 92 91 94 93 99 98 97 86 87 85 89 88 "
    REQUIRE(ss == "3 8 56 93 32 98 96 91 90 32 99 98 96 86 91 89 92 99 85 89 87 92 85 ");

    delete graph;
}

// // Dikstra's (???)
// TEST_CASE("testShortestPathEmpty", "[weight=1][part=2]")
// {
//     // testing traversing the tree for at least one empty variable
//     REQUIRE(true);
// }
// TEST_CASE("testShortestPath1 dataset1", "[weight=1][part=2]")
// {
//     // testing traversing the tree for the shortest path (dataset 1)
//     REQUIRE(true);
// }
// TEST_CASE("testShortestPath2 dataset1", "[weight=1][part=2]")
// {
//     // testing traversing the tree for the shortest path (dataset 1)
//     REQUIRE(true);
// }
// TEST_CASE("testShortestPath3 dataset2", "[weight=1][part=2]")
// {
//     // testing traversing the tree for the shortest path (dataset 2)
//     REQUIRE(true);
// }
// TEST_CASE("testShortestPath4 dataset2", "[weight=1][part=2]")
// {
//     // testing traversing the tree for the shortest path (dataset 2)
//     REQUIRE(true);
// }

// #endif
