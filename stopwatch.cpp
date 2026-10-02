//simple stopwatch to time programs
//call start() to start timing
//call stop() to stop timing
//time difference can be output in either seconds (double) or nanoseconds (long long)
#include "stopwatch.hpp"
    StopWatch::StopWatch(): startTime(), endTime() {}
    void StopWatch::start() {
        startTime = std::chrono::high_resolution_clock::now();
    }
    void StopWatch::stop() {
        endTime = std::chrono::high_resolution_clock::now();
    }
    double StopWatch::getElapsedTimeSeconds() {
        std::chrono::duration<double> elapsed = endTime - startTime;
        return elapsed.count();
    }
    unsigned long long StopWatch::getElapsedTimeNs() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    }