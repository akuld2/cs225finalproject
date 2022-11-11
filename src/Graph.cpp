#include "Graph.h"
#include <string>
#include <fstream>
#include <vector>
#include <utility>  
#include <stdexcept> 
#include <sstream>   
#include <iostream>

Graph::Graph(std::string filename)
{
    buildGraph(filename);
}

Node *Graph::graphIterator(std::string zoneName)
{
    // goes through all of the nodes and sees if the zone exists
    Node *newZone = getNode(zoneName);
    if (newZone != NULL) {
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
};