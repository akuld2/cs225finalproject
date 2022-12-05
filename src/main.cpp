#include "Graph.h"
#include "Edge.h"
#include "Node.h"

#include <algorithm>
#include <iostream>

int main()
{
    Graph* taxiGraph = new Graph("datasets/Taxi_Trips.csv");
    taxiGraph->printGraph();
    std::vector<std::string> zones = taxiGraph->getNodeNames();
    bool quitSelected = false;

    std::cout << "Welcome to the Chicago Taxi Trip Navigator!" << std::endl;

    while (quitSelected == false) {
        std::cout << "Please select an Option: " << std::endl;
        std::cout << "1.) Navigate Between Zones" << std::endl;
        std::cout << "2.) Navigate to Connected Zones" << std::endl;
        std::cout << "3.) Find The Busiest Zone" << std::endl;
        std::cout << "4.) Quit" << std::endl;
        std::cout << std::endl;

        int choice;
        std::cin >> choice;
        std::cout << std::endl;

        int startingLocation;
        int endingLocation;

        if (choice == 1) { 
            std::cout << "You have selected to navigate between zones." << std::endl;
            std::cout << "Available Zones: ";
            taxiGraph->printNodes(); 
            std::cout << std::endl;
            std::cout << "Please select a starting zone." << std::endl;
            std::cin >> startingLocation;
            std::cout << "Please select an ending zone." << std::endl;
            std::cin >> endingLocation;
            std::cout << std::endl;
            if (std::find(zones.begin(), zones.end(), std::to_string(startingLocation)) != zones.end() && std::find(zones.begin(), zones.end(), std::to_string(endingLocation)) != zones.end()) {
                std::cout << "Please select an option to minimize: " << std::endl;
                std::cout << "1.) Fare" << std::endl;
                std::cout << "2.) Time" << std::endl;
                std::cout << "3.) Miles" << std::endl;
                int choice2;
                std::cin >> choice2;
                std::vector<Node*> path;
                if (choice2 == 1) {
                    // path =
                } else if (choice2 == 2) {
                    // path = 
                } else if (choice2 == 3) {
                    // path = 
                } else {
                    std::cout << "Choice entered is invalid." << std::endl;
                }
                std::cout << "Navigation Order: ";
                for (Node* node : path) {
                    std::cout << node->getZone() << " "; 
                }
                std::cout << std::endl;
            } else { 
                std::cout << "One or both of the zones entered are invalid." << std::endl;
            }
        } else if (choice == 2) {
            std::cout << "You have selected to navigate to all zones." << std::endl;
            std::cout << "Available Zones: ";
            taxiGraph->printNodes(); 
            std::cout << std::endl;
            std::cout << "Please select a starting zone." << std::endl;
            std::cin >> startingLocation;
            std::cout << std::endl;
            if (std::find(zones.begin(), zones.end(), std::to_string(startingLocation)) != zones.end()) {
                std::vector<Node*> path = taxiGraph->BFS(taxiGraph->getNode(std::to_string(startingLocation)));
                std::cout << "Navigation Order: ";
                for (Node* node : path) {
                    std::cout << node->getZone() << " "; 
                }
                std::cout << std::endl;
            } else {
                std::cout << "Zone entered is invalid." << std::endl;
            }
        } else if (choice == 3) {
            std::cout << "You have selected to find the most busy zone." << std::endl;
            std::cout << "The busiest zone is when minimizing fare is  " << taxiGraph->betweennessCentrality(0) << std::endl;
            std::cout << "The busiest zone is when minimizing time is  " << taxiGraph->betweennessCentrality(1) << std::endl;
            std::cout << "The busiest zone is when minimizing distance is  " << taxiGraph->betweennessCentrality(2) << std::endl;
        } else if (choice == 4) {
            std::cout << "Thank you for your patronage. Good day." << std::endl;
            quitSelected = true;
        } else {
            std::cout << "You have input an invalid option. Goodbye." << std::endl;
            quitSelected = true;
        }
        std::cout << std::endl;
    }

    delete taxiGraph;
}