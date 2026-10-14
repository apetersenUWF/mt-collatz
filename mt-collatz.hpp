/**
* mt-collatz.hpp
*
* Ayden Petersen
* Jackson Puls
* Project 2 - mt-collatz
* 
*/
#pragma once

#include "histogram.hpp"
#include <atomic>

//A struct used to hold the results of the Collatz sequence so it can all be returned from start_collatz
struct CollatzResults {
    uint64_t time; //An integer representing the runtime in nanoseconds
    Histogram* histogram; //A histogram holding the frequencies of each stopping time
};

//A class to run the multi-threaded collatz sequence for a given length N and thread count T
class MT_COLLATZ {
    private:
        uint64_t N; //An integer representing the number of stopping times to be computed
        uint8_t T; //An integer representing the number of threads to use
        uint64_t chunk_size; //An integer representing the number of stoptimes handed to each thread to compute in one chunk, computed automatically based on MAX_CHUNK_SIZE T and N

        std::atomic<uint64_t> COUNTER{1}; // Shared counter the threads will pull from. It's atomic to prevent race conditions. From my testing it's as accurate and incredibly fast compared to std::mutex.
        
        //This array is used by calc_collatz_stoptime to cache previously calculated stop times, since a lot of numbers will repeat the same paths. This speeds up the program a crap ton.
        //Since its a member variable, do each run with a new MT_COLLATZ object for accurate times
        uint16_t* collatz_cache; 

        /*
        * A function that calculates the collatz sequence stopping time for a certain number n
        * Checks the cache for a memoized result after each step for speed gains
        * Stores the result in the cache for later lookup
        * @ param int n: the number to compute the collatz sequence stop time of
        */
        uint64_t calcCollatzStoptime(uint64_t n);
        /*
        * The function each indicidual thread will work on concurrently
        * Determines the range of stopping times the thread will compute based on the chunk_size and current counter value
        * Loops through each number in the block of work and computes all the stopping times
        * Increments the atomic counter by chunk size so the other threads know where to work
        * Stores frequencies in the local histogram h
        * @ param uint64_t* h: a pointer to an array of integers that stores the frequency of stopping times found by the thread
        * Each thread gets its own local histogram that are all merged at the end
        */
        void threadWorker(uint64_t* h);
    public:
        /*
        * Function that constructs an MT_COLLATZ object
        * Assigns member variables N and T, calculates the chunk_size, and initializes an empty collatz_cache
        * @ param uint64_t N: The number of stopping times to be computed
        * @ uint8_t T: The number of threads to be used
        */
        MT_COLLATZ(uint64_t N, uint8_t T);
        /*
        * Function that cleans up the MT_COLLATZ object
        * Frees the collatz_cache
        */
        ~MT_COLLATZ();
        /*
        * A function that starts computing the collatz sequence up to the number N using T threads
        * Initializes all of the threads with the thread worker function
        * Initializes all of the empty local histograms for each thread
        * Uses the StopWatch to time how long the sequence takes to compute
        * Waits for all the threads to join before recording the time and merging all of the local histogrrams
        * Returns a struct containing the time to complete and the merged histogram
        */
        CollatzResults startCollatz();
};
