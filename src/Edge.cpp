#include "Edge.h"
#include <iostream>

Edge::Edge() {}

Edge::Edge(double newFare, double newMiles, double newTime) {
    fare_ = newFare;
    miles_ = newMiles;
    time_ = newTime;
    incrementTotal();
}


double Edge::getFare() {
    return fare_;
}

double Edge::getMiles() {
    return miles_;
}

double Edge::getTime() {
    return time_;
}

void Edge::incrementTotal() {
    total_++;
}

void Edge::averageFare(double newFare) {
    fare_ = ((fare_*total_) + newFare) / (total_+1);
}

void Edge::averageMiles(double newMiles) {
    miles_ = ((miles_*total_) + newMiles) / (total_+1);
}

void Edge::averageTime(double newTime) {
    time_ = ((time_*total_) + newTime) / (total_+1);
}
