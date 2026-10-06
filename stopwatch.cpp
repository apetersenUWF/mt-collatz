/**
* stopwatch.cpp
*
* Ayden Petersen
* Jackson Puls
* Project 2 - mt-collatz
*
*/
#include "stopwatch.hpp"

StopWatch::StopWatch(): startTime(), endTime() {} //Default constructor, start with empty start and end times

void StopWatch::start() { //Begin timing, record startTime using system clock
    startTime = std::chrono::high_resolution_clock::now();
}
void StopWatch::stop() { //Stop timing, record endTime using system clock
    endTime = std::chrono::high_resolution_clock::now();
}
double StopWatch::getElapsedTime() { //Return elapsed time in seconds
    std::chrono::duration<double> elapsed = endTime - startTime;
    return elapsed.count();
}
unsigned long long StopWatch::getElapsedTimeNs() { //Return elapsed time in nanoseconds
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}