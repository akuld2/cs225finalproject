#include "../src/Graph.h"
#include "../src/Edge.h"
#include "../src/Node.h"

#include <iostream>

int main() {
    Graph myGraph;
    
    std::vector<Graph::TaxiTripDetails> result = myGraph.read_csv("Taxi_Trips.csv");
    for (auto taxiTrip: result) {
        std::cout << taxiTrip.pickupLocation << "  " << taxiTrip.dropoffLocation << std::endl;
    }
    // int start_x; // starting numerical value for place1
    // int start_y; //starting numerical value for place2
    // int end_x; // ending numerical value for place1
    // int end_y; // ending numerical value for place2

    // std::cout << "Enter the x coordinate for your starting point: ";
    // std::cin >> start_x;
    // std::cout << std::endl;
    // std::cout << "Enter the y coordinate for your starting point: ";
    // std::cin >> start_y;
    // std::cout << std::endl;
    // std::cout << "Enter the x coordinate for your destination: ";
    // std::cin >> end_x;
    // std::cout << std::endl;
    // std::cout << "Enter the y coordinate for your destination: ";
    // std::cin >> end_y;
}