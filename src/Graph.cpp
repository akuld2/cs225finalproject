#include "Graph.h"
/*
#include <algorithm>
#include <queue>
#include <iostream>
#include <cfloat>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream>
*/

std::vector<Node*>* Graph::getNodes() {
    return &nodes_;
}

unsigned int Graph::getSize() {
    return nodes_.size();
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

Graph::Graph(std::string filename)
{
    buildGraph(filename);
}

Graph::Graph(std::vector<Node*> nodes) { //TODO: delete after updating tests
    nodes_ = nodes;
}

Node *Graph::graphIterator(std::string zoneName)
{
    // goes through all of the nodes and sees if the zone exists
    Node *newZone = getNode(zoneName);
    if (newZone != NULL)
    {
        return newZone;
    }
    // if it doesn't exist, will create a new node, add it to the zone list, and then return it
    newZone = new Node(zoneName);
    nodes_.push_back(newZone);
    return newZone;
}

void Graph::buildGraph(std::string filename)
{
    std::vector<Graph::TaxiTripDetails> result = readCSV(filename);
    // iterates through entire csv
    for (auto taxi : result)
    {
        // will rerieve or create the nodes
        Node *iterPickup = graphIterator(taxi.pickupLocation);
        Node *iterDropoff = graphIterator(taxi.dropoffLocation);

        try
        {
            Edge *edge = ((iterPickup)->retrieveNeighborEdge(iterDropoff));
            // if no error after this, we just average the edge characteristics
            edge->averageFare(taxi.tripFare);
            edge->averageMiles(taxi.tripMiles);
            edge->averageTime(taxi.tripSecond);
            edge->incrementTotal();
        }
        catch (...)
        {
            // if error, then there is no edge and we must create one
            Edge *edge = new Edge(taxi.tripFare, taxi.tripMiles, taxi.tripSecond);
            (iterPickup)->addEdge(*iterDropoff, *edge);
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
            // if the colName is one of the desired columns that we need information, we will keep track of the index
            if (colName == "Trip Seconds" || colName == "Trip Miles" ||
                colName == "Fare" || colName == "Pickup Community Area" ||
                colName == "Dropoff Community Area")
            {

                columnInfo[colName] = colIndex;
            }
            colIndex++;
        }
        // one more check because if there is no comma at the end...
        if (colName == "Trip Seconds" || colName == "Trip Miles" ||
            colName == "Fare" || colName == "Pickup Community Area" ||
            colName == "Dropoff Community Area")
        {

            columnInfo[colName] = colIndex;
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
            // if any of the fields are empty, won't add at all
            if (seconds != "" && pickup != "" && dropoff != "" && fare != "" && miles != "")
            {
                // ensures no self loops
                if (taxiData.at(columnInfo["Pickup Community Area"]) != taxiData.at(columnInfo["Dropoff Community Area"]))
                {
                    // check to make sure all entries are there
                    result.push_back(TaxiTripDetails(std::stod(seconds),
                                                     std::stod(miles), std::stod(fare),
                                                     pickup, dropoff));
                }
            }
        }
    }
    

    // Close file
    myFile.close();
    return result;
}






std::vector<std::pair<Node*, double>> Graph::findPathLengths(Node* start, int metric) {
    std::vector<std::pair<Node*, double>> distances = 
        std::vector<std::pair<Node*, double>>(nodes_.size());

    distances.push_back(std::pair<Node*, double>(start, 0));
    for (unsigned int i = 1; i < nodes_.size(); i++) {
        distances.push_back(std::pair<Node*, double>(nodes_[i], DBL_MAX));
    }

    std::queue<Node*> queue;
    queue.push(start);
    while (!queue.empty()) {
        Node* front = queue.front();
        queue.pop();

        for (auto neighbor : *(front->getNeighbors())) {
            Edge* edge = neighbor.second;
            Node* destination = neighbor.first;

            int index = get_idx_path(distances, front);
            
            int val_to_add = 0;
            if (metric == 0) {
                val_to_add = edge->getFare();
            }
            else if (metric == 1) {
                val_to_add = edge->getMiles();
            }
            else if (metric == 2) {
                val_to_add = edge->getTime();
            }
            else {
                distances[0].second = -1.0; // metric has to be 0-2.
                return distances;
            }


            auto new_dist = val_to_add + get_seconds_path(distances)[index];
            
            index = get_idx_path(distances, destination);
            if (new_dist < get_seconds_path(distances)[index]) {
                distances[index].second = new_dist;
                queue.push(destination);
            }
        }
    }
    return distances;
}

double Graph::findShortestPath(Node* start, Node* end, int metric) {
    std::vector<std::pair<Node*, double>> distances = findPathLengths(start, metric);

    int index = get_idx_path(distances, end);
    return distances[index].second;
}


int Graph::get_idx_path(std::vector<std::pair<Node*, double>> distances, Node* destination) {
    std::vector<Node*> firsts;
    for (unsigned int i = 0; i < distances.size(); i++) {
        if (distances[i].first == destination) {
            return (int) i;
        }
    }
    return -1;
}

std::vector<double> Graph::get_seconds_path(std::vector<std::pair<Node*, double>> distances) {
    std::vector<double> seconds;
    for (unsigned int i = 0; i < distances.size(); i++) {
        seconds.push_back(distances[i].second);
    }
    return seconds;
}

std::vector<Node*> Graph::get_firsts_path(std::vector<std::pair<Node*, double>> distances) {
    std::vector<Node*> firsts;
    for (unsigned int i = 0; i < distances.size(); i++) {
        firsts.push_back(distances[i].first);
    }
    return firsts;
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
    std::vector<Node*> visitedNodes; 
    std::queue<Node*> queue;
    // std::stack<Node*> queue;
    std::vector<Node*> order;

    queue.push(start);
    visitedNodes.push_back(start);

    while (!queue.empty()) {
        Node* top = queue.front();
        // Node* top = queue.top();
        queue.pop();
        order.push_back(top);
        std::cout << "top: " << top->getZone() <<std::endl;

        std::map<Node *, Edge *>::iterator it;
        
        for (it = top->getNeighbors()->begin(); it != top->getNeighbors()->end(); it++) {
            if (!visited(it->first, visitedNodes)) {
                std::cout << "      add: " << it->first->getZone() <<std::endl;
                queue.push(it->first);
                visitedNodes.push_back(it->first);
            }
        }
    }
    // for (auto node : cheapestPath) {
    //     std::cout << node->getZone() << ", ";
    // }
    // std::cout << std::endl;
    return order;
}