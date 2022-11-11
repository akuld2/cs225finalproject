#include "Edge.h"

Edge::Edge(double newFare, double newMiles, double newTime) {
    fare_ = newFare;
    miles_ = newMiles;
    time_ = newTime;
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

void Edge::averageFare(double newFare) {
    fare_ = (fare_ + newFare) / 2;
}

void Edge::averageMiles(double newMiles) {
    miles_ = (miles_ + newMiles) / 2;
}

void Edge::averageTime(double newTime) {
    time_ = (time_ + newTime) / 2;
}
