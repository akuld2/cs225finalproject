#include "Graph.h"
#include <string>
#include <fstream>
#include <vector>
#include <utility>   // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream>   // std::stringstream

std::vector<Node> *Graph::getNodes()
{
    return &nodes_;
}

Node *Graph::getNode(std::string zone)
{
    for (unsigned i = 0; i < nodes_.size(); ++i)
    {
        if (nodes_.at(i).getZone() == zone)
        {
            return &nodes_.at(i);
        }
    }
    return NULL;
}

std::vector<Graph::TaxiTripDetails> Graph::read_csv(std::string filename)
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
    int val;
    std::map<std::string, unsigned> columnInfo;

    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        std::stringstream ss(line);
        unsigned colIndex = 0;
        while (std::getline(ss, colName, ','))
        {
            if (colName == "Trip Seconds" || colName == "Trip Miles" ||
                colName == "Fare" || colName == "Pickup Community Area" ||
                colName == "Dropoff Community Area")
            {
                columnInfo[colName] = colIndex;
            }
            colIndex++;
        }
    }
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
        result.push_back(TaxiTripDetails(std::stod(taxiData.at(columnInfo["Trip Seconds"])), 
            std::stod(taxiData.at(columnInfo["Trip Miles"])), std::stod(taxiData.at(columnInfo["Fare"])), 
            taxiData.at(columnInfo["Pickup Community Area"]), taxiData.at(columnInfo["Dropoff Community Area"])));
    }

    // Close file
    myFile.close();

    return result;
};