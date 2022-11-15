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
TEST_CASE("testTraverse1", "[weight=1][part=2]")
{
    // testing traversing the tree for the shortest path (dataset smallBasic)
    Graph *graph = new Graph("datasets/smallBasic.csv");
    std::vector<Node*> path = graph->BFS(graph->getNodes()->at(0)); // first node is 1

    std::string ss = "";
    for (unsigned i = 0; i < path.size(); i++) {
        ss += path.at(i)->getZone() + " ";
    }
    REQUIRE(ss == "1 2 3 ");

    delete graph;
}

TEST_CASE("testTraverse2", "[weight=1][part=2]")
{
    // testing traversing the tree for the shortest path (dataset mediumBasic)
    Graph *graph = new Graph("datasets/mediumBasic.csv");
    std::vector<Node*> path = graph->BFS(graph->getNodes()->at(0)); // first node is 7

    std::string ss = "";
    for (unsigned i = 0; i < path.size(); i++) {
        ss += path.at(i)->getZone() + " ";
    }
    REQUIRE(ss == "7 24 3 8 56 32 43 ");

    delete graph;
}

TEST_CASE("testTraverse3", "[weight=1][part=2]")
{
    // testing traversing the tree for the shortest path (dataset hardBasic)
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