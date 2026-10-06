/**
* histogram.hpp
*
* Ayden Petersen
* Jackson Puls
*
*/
#pragma once

#include <string>

//Histogram class holds frequency data for stopping times
class Histogram {
private:
    int k; //The upper limit for stopping times that the histogram will track, should be > 0
    int* frequencies; //The array storing the frequencies of each stopping time: size k + 1
public:
    /*
    * Constructs an empty Histogram object
    * @param k sets the upper bound of the histogram
    * k = 1000 by default so frequencies 0 to 1000 will be tracked
    */
    Histogram(int k = 1000);
    /*
    * Histogram destructor, deallocates frequencies array
    */
    ~Histogram();
    /*
    *                   Print frequencies to stdout in the format:
    *                   0,frequency_of_stopping_time(0)
    *                   1,frequency_of_stopping_time(1)
    *                   2,frequency_of_stopping_time(2)
    *                   ...
    */
    void print() const; 
    /*
    * Increments the cooresponding frequency index
    * ex : frequencies[5] = 2 -> updateFrequency(5) -> frequencies[5] = 3
    * @param stoppingTime The stopping time found by the collatz sequence that will be incremented in the histogram
    */
    bool updateFrequency(int stoppingTime); 
};