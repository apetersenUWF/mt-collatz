#pragma once

#include <string>
class Histogram {
private:
    int k; //The upper limit for stopping times that the histogram will track, dictated by project 2 requirements
    int* frequencies; //The array storing the frequencies of each stopping time
public:
    Histogram(int k = 1000); //Default k = 1000, dictated by project requirements
    ~Histogram();
    void print() const; //Print frequencies to stdout in the format:
                        //0,frequency_of_stopping_time(0)
                        //1,frequency_of_stopping_time(1)
                        //2,frequency_of_stopping_time(2)
                        //…
    bool updateFrequency(int stoppingTime); //Increments the cooresponding stopping time counter
                                            //For example if a thread finds a stopping time of 6
                                            //call updateFrequency(6)
};