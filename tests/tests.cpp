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

Graph createGraph1() {
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

// Basic test cases
TEST_CASE("initializeGraph1", "[weight=1][part=1]") {
    // initialize and validate creating the graph with 5 test values
    Graph graph = createGraph1();
    REQUIRE(!(graph.getNodes()->empty()));
}

TEST_CASE("testGraph1", "[weight=1][part=2]") {
    Graph graph = createGraph1();
    REQUIRE(graph.getNode("1") != nullptr);
    REQUIRE(graph.getNode("2") != nullptr);
    auto distances = graph.findPathLengths(graph.getNode("1"), 1);
    REQUIRE(!distances.empty());
    /*std::cout << "test1" << std::endl;

    for (unsigned int i = 0; i < distances.size(); i++) {
        std::cout << i << " " << distances[i].second << std::endl;
    }
    
    std::cout << "test2" << std::endl;*/

    REQUIRE(graph.findShortestPath(graph.getNode("1"), graph.getNode("2"), 1) == 1.0);
    REQUIRE(graph.findShortestPath(graph.getNode("1"), graph.getNode("3"), 1) == 3.0);
    REQUIRE(graph.findShortestPath(graph.getNode("1"), graph.getNode("4"), 1) == 6.0);
    REQUIRE(graph.findShortestPath(graph.getNode("1"), graph.getNode("5"), 1) == 5.0);
}

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



// Advanced test cases
TEST_CASE("test BFS path small", "[weight=1][part=2]")
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

TEST_CASE("test BFS path medium", "[weight=1][part=2]")
{
    // testing traversing the tree for the cheapest path (dataset mediumBasic)
    Graph *graph = new Graph("datasets/mediumBasic.csv");
    std::vector<Node*> path = graph->BFS(graph->getNodes()->at(0)); // first node is 7

    std::string ss = "";
    for (unsigned i = 0; i < path.size(); i++) {
        ss += path.at(i)->getZone() + " ";
    }
    bool isCorrect = ((ss == "7 24 3 8 56 32 43 ")||(ss == "7 24 3 8 56 43 32 "));
    REQUIRE(isCorrect);

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
