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

void Graph::buildGraph(std::string filename)
{
    std::vector<Graph::TaxiTripDetails> result = readCSV(filename);
    for (auto taxi : result)
    {
        std::cout << taxi.pickupLocation << " - " << taxi.dropoffLocation << std::endl;
        Node *taxiInfoBegin = new Node(taxi.pickupLocation);
        Node *taxiInfoDropOff = new Node(taxi.pickupLocation);
        std::vector<Node *>::iterator iterPickup = std::find(nodes_.begin(), nodes_.end(), taxiInfoBegin);
        std::vector<Node *>::iterator iterDropoff = std::find(nodes_.begin(), nodes_.end(), taxiInfoDropOff);
        if (iterDropoff != nodes_.end())
        {
            if (iterPickup != nodes_.end())
            {

                try
                {
                    Edge *edge = ((*iterPickup)->retrieveNeighborEdge(**iterDropoff));
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
                    (*iterPickup)->addEdge(**iterDropoff, *edge);
                }
            }
            else
            {
                // adds the new edge and the new node
                Edge *edge = new Edge(taxi.tripFare, taxi.tripMiles, taxi.tripSecond);
                taxiInfoBegin->addEdge(**iterDropoff, *edge);
                nodes_.push_back(taxiInfoBegin);
            }
        }
        else
        {
            if (iterPickup != nodes_.end())
            {

                try
                {
                    Edge *edge = ((*iterPickup)->retrieveNeighborEdge(*taxiInfoDropOff));
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
                    (*iterPickup)->addEdge(*taxiInfoDropOff, *edge);
                }
            }
            else
            {
                // adds the new edge and the new node
                Edge *edge = new Edge(taxi.tripFare, taxi.tripMiles, taxi.tripSecond);
                taxiInfoBegin->addEdge(*taxiInfoDropOff, *edge);
                nodes_.push_back(taxiInfoBegin);
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

// std::vector<Node> *Graph::getNodes()
// {
//     return &nodes_;
// }

// Node *Graph::getNode(std::string zone)
// {
//     for (unsigned i = 0; i < nodes_.size(); ++i)
//     {
//         if (nodes_.at(i).getZone() == zone)
//         {
//             return &nodes_.at(i);
//         }
//     }
//     return NULL;
// }