#include "Graph.h"
#include <string>
#include <fstream>
#include <vector>
#include <utility>   // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream>   // std::stringstream
#include <iostream>

Graph::Graph(std::string filename)
{
    // @todo need to fix build graph and readCSV
    buildGraph(filename);
}

Node* Graph::myIterator(Node* tmp) {
    for (unsigned i = 0; i < nodes_.size(); ++i) {
        if (nodes_.at(i)->getZone() == tmp->getZone()) {
            return nodes_.at(i);
        }
    }
    return NULL;
}

void Graph::buildGraph(std::string filename)
{
    std::vector<Graph::TaxiTripDetails> result = readCSV(filename);
    for (auto taxi : result)
    {
        Node *taxiInfoBegin = new Node(taxi.pickupLocation);
        Node *taxiInfoDropOff = new Node(taxi.dropoffLocation);
        Node* iterPickup = myIterator(taxiInfoBegin);
        Node* iterDropoff = myIterator(taxiInfoDropOff);
        if (iterDropoff != NULL)
        {
            if (iterPickup != NULL)
            {
                try
                {
                    Edge *edge = ((iterPickup)->retrieveNeighborEdge(iterDropoff));
                    // if no error after this, we just average it
                    edge->averageFare(taxi.tripFare);
                    edge->averageMiles(taxi.tripMiles);
                    edge->averageTime(taxi.tripSecond);
                }
                catch (...)
                {
                    // if error, then there is no edge and we must create
                    Edge *edge = new Edge(taxi.tripFare, taxi.tripMiles, taxi.tripSecond);
                    // todo check if end node exists
                    (iterPickup)->addEdge(*iterDropoff, *edge);
                }
            }
            else
            {
                // adds the new edge and the new node
                Edge *edge = new Edge(taxi.tripFare, taxi.tripMiles, taxi.tripSecond);
                taxiInfoBegin->addEdge(*iterDropoff, *edge);
                nodes_.push_back(taxiInfoBegin);
            }
        }
        else
        {
            if (iterPickup != NULL)
            {
                nodes_.push_back(taxiInfoDropOff);
                try
                {
                    Edge *edge = ((iterPickup)->retrieveNeighborEdge(taxiInfoDropOff));
                    // if no error after this, we just average it
                    edge->averageFare(taxi.tripFare);
                    edge->averageMiles(taxi.tripMiles);
                    edge->averageTime(taxi.tripSecond);
                }
                catch (...)
                {
                    // if error, then there is no edge and we must create
                    Edge *edge = new Edge(taxi.tripFare, taxi.tripMiles, taxi.tripSecond);
                    // todo check if end node exists
                    (iterPickup)->addEdge(*taxiInfoDropOff, *edge);
                }
            }
            else
            {
                // adds the new edge and the new node
                Edge *edge = new Edge(taxi.tripFare, taxi.tripMiles, taxi.tripSecond);
                taxiInfoBegin->addEdge(*taxiInfoDropOff, *edge);
                nodes_.push_back(taxiInfoBegin);
                nodes_.push_back(taxiInfoDropOff);
            }
        }
    }
}

std::vector<Graph::TaxiTripDetails> Graph::readCSV(std::string filename)
{

    std::vector<TaxiTripDetails> result;
    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if (!myFile.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    std::string colName;
    std::map<std::string, unsigned> columnInfo;
    unsigned colIndex = 0;
    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        std::stringstream ss(line);

        while (std::getline(ss, colName, ','))
        {
            std::cout << "colname: " << colName << std::endl;
            if (colName == "Trip Seconds" || colName == "Trip Miles" ||
                colName == "Fare" || colName == "Pickup Community Area" ||
                colName == "Dropoff Community Area")
            {
                columnInfo[colName] = colIndex;
            }
            colIndex++;
        }
    }
    const unsigned NUM_COL = colIndex;
    int lines = 0;
    // Read data, line by line
    while (std::getline(myFile, line) && lines < 10000)
    {
        lines++;
        std::stringstream ss(line);
        std::string data;
        std::vector<std::string> taxiData;
        while (std::getline(ss, data, ','))
        {
            taxiData.push_back(data);
        }
        // need to add additional checks here
        // ensures that all the data is there per taxi
        if (NUM_COL == taxiData.size())
        {
            // makes sure that they are not empty strings
            std::string seconds = (taxiData.at(columnInfo["Trip Seconds"]));
            seconds.erase(remove(seconds.begin(), seconds.end(), ' '), seconds.end());
            std::string pickup = (taxiData.at(columnInfo["Pickup Community Area"]));
            pickup.erase(remove(pickup.begin(), pickup.end(), ' '), pickup.end());
            std::string dropoff = (taxiData.at(columnInfo["Dropoff Community Area"]));
            dropoff.erase(remove(dropoff.begin(), dropoff.end(), ' '), dropoff.end());
            std::string fare = (taxiData.at(columnInfo["Fare"]));
            fare.erase(remove(fare.begin(), fare.end(), ' '), fare.end());
            std::string miles = (taxiData.at(columnInfo["Trip Miles"]));
            miles.erase(remove(miles.begin(), miles.end(), ' '), miles.end());
            if (seconds != " " && pickup != " " && dropoff != " " && fare != " " && miles != " ")
            {
                // ensures no self loops
                if (taxiData.at(columnInfo["Pickup Community Area"]) != taxiData.at(columnInfo["Dropoff Community Area"]))
                {
                    // check to make sure all entries are there
                    result.push_back(TaxiTripDetails(std::stod(taxiData.at(columnInfo["Trip Seconds"])),
                                                     std::stod(taxiData.at(columnInfo["Trip Miles"])), std::stod(taxiData.at(columnInfo["Fare"])),
                                                     taxiData.at(columnInfo["Pickup Community Area"]), taxiData.at(columnInfo["Dropoff Community Area"])));
                }
            }
        }
    }

    // Close file
    myFile.close();
    return result;
};

std::vector<Node *> *Graph::getNodes()
{
    return &nodes_;
}

Node *Graph::getNode(std::string zone)
{
    for (unsigned i = 0; i < nodes_.size(); ++i)
    {
        if (nodes_.at(i)->getZone() == zone)
        {
            return nodes_.at(i);
        }
    }
    return NULL;
}

void Graph::printGraph() const
{
    for (auto node : nodes_)
    {
        std::cout << "pickup: " << node->getZone() << std::endl;
        std::map<Node *, Edge *>::iterator it;

        for (it = node->getNeighbors()->begin(); it != node->getNeighbors()->end(); it++)
        {
            std::cout << "      dropoff: " << it->first->getZone() << " --$" << it->second->getFare() << std::endl;
        }
        std::cout << "----------" << std::endl;
    }
}

bool Graph::visited(Node* node, std::vector<Node*> vec) {
    for (unsigned i = 0; i < vec.size(); ++i) {
        if (vec.at(i)->getZone() == node->getZone()) {
            return true;
        }
    }
    return false;
}

std::vector<Node*> Graph::BFS(Node* start) {
    std::vector<Node*> cheapestPath;
    std::vector<Node*> visitedNodes; 
    std::queue<Node*> queue;

    cheapestPath.push_back(start);
    queue.push(start);
    visitedNodes.push_back(start);
    
    while (!queue.empty()) {
        Node* top = queue.front();
        queue.pop();

        std::map<Node *, Edge *>::iterator it;
        Node* minNode = NULL;
        double minFare = DBL_MAX;
        
        for (it = top->getNeighbors()->begin(); it != top->getNeighbors()->end(); it++) {
            if (!visited(it->first, visitedNodes)) {
                queue.push(it->first);
                visitedNodes.push_back(it->first);
                if (it->second->getFare() < minFare) {
                    minFare = it->second->getFare();
                    minNode = it->first;
                }
            }
        }
        if (minNode != NULL) {
            cheapestPath.push_back(minNode);
        } else {
            cheapestPath.push_back(top);
        }
    }
    
    // for (auto node : cheapestPath) {
    //     std::cout << node->getZone() << ", ";
    // }
    // std::cout << std::endl;
    return cheapestPath;
}