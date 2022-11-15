#pragma once

class Edge
{
public:
    Edge(double newFare, double newMiles, double newTime);
    /**
     * getFare will get the fare of the trip
     * @return fare_
     */
    double getFare();

    /**
     * getMiles will return the miles travelled
     * @return miles_
     */
    double getMiles();

    /**
     * getTime will return the time of the trip
     * @return time_
     */
    double getTime();

    /**
     * averageFare will input the new fare and will average it with the existing fare
     * @param newFare is the fare we need to include in the average
     */
    void averageFare(double newFare);

    /**
     * averageMiles will input the new mile and will average it with the existing mile
     * @param newMiles is the miles we need to include in the average
     */
    void averageMiles(double newMiles);

    /**
     * averageTime will input the new time and will average it with the existing time
     * @param newTime is the time we need to include in the average
     */
    void averageTime(double newTime);

    /**
     * increment total will increment the number of edges we are averaging
     */
    void incrementTotal();

private:
    double fare_;
    double miles_;
    double time_;
    unsigned total_ = 0;
};