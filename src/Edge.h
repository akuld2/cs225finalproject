#pragma once

class Edge {
    public:
        double getFare();
        double getMiles();
        double getTime();
        void averageFare(double newFare);
        void averageMiles(double newMiles);
        void averageTime(double newTime);
    private:
        double fare_;
        double miles_;
        double time_;
};