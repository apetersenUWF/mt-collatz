/**
* stopwatch.hpp
*
* Ayden Petersen
* Jackson Puls
* Project 2 - mt-collatz
*
*/
#pragma once
#include <chrono>
//Class used to time programs 
class StopWatch {
    private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime; /* Holds the times that the clock started and ended
                                                                                       Populated by calling start() and stop()      */
    public:
        /*
        * Constructs an empty stopwatch object
        */
        StopWatch();
        /*
        * Starts timing, records start time, stores in startTime
        */
        void start();
        /*
        * Stops timing, records stop time, stores in endTime
        */
        void stop();
        /*
        * Returns the difference between the stop time and start time in seconds
        */
        double getElapsedTime();
        /*
        * Returns the difference between the stop time and start time in nanoseconds
        */
        unsigned long long getElapsedTimeNs();
};