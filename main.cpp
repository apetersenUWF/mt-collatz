/**
* main.cpp
*
* Ayden Petersen
* Jackson Puls
* Project 2 - mt-collatz
* 
*/
#include "mt-collatz.hpp"
#include "histogram.hpp"
#include "parse.hpp"

using namespace std;

/*
*
MAIN
*
*/
int main(int argc, char** argv) {
    if (argc < 3 || argc > 5) { //must be 3 or 5 arguments ./mt-collatz <N> <T> [i] [-nocache]
        cerr << "Invalid input, please pass the form <N> <T> [i] [-nocache]" << endl;
        return 1;
    }
    //non-optional arguments <N, T>
    uint64_t N = parsePositive(argv[1], "N", ULLONG_MAX);
    uint8_t T = static_cast<uint8_t>(parsePositive(argv[2], "T", UINT8_MAX));

    //optional arguments [i] and [-nocache]
    uint32_t i = parseOptionalArgs(argc, argv); //sets i and NO_CACHE, i is 1 and NO_CACHE is false by default

    uint64_t times[i]; //array to store the runtime of each collatz sequence iteration

    for (uint32_t j = 0; j < i; j++) { //iterate over i repeating the program each time
        MT_COLLATZ collatz(N, T); //initialize collatz object with user defined parameters
        CollatzResults result = collatz.startCollatz(); //compute the collatz sequence, return runtime and histogram
        times[j] = result.time;
        Histogram* histo = result.histogram;
        if (j == i - 1) histo->print(); // Print on last (doesn't affect the results, just keeps the output less cluttered)
        delete histo; //free up the memory from the histogram
    }

    uint64_t avgTime = 0;

    cerr << "Times: " << endl;

    for (uint32_t j = 0; j < i; j++) { //prints times for each run
        cerr << times[j] << endl;
        avgTime += times[j];
    }
    cerr << endl;
    
    avgTime/=i;

    cerr << N << ", " << (int)T << ", " << "average time: " << avgTime << " ns" << endl; // Output time to std::cerr
    return 0;
}