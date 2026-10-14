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
    if (argc < 3 || argc > 4) {
        cerr << "Invalid input, please pass the form <N T i>" << endl;
        return 1;
    }
    //non-optional arguments <N, T>
    uint64_t N = parsePositive(argv[1], "N", ULLONG_MAX);
    uint8_t T = static_cast<uint8_t>(parsePositive(argv[2], "T", UINT8_MAX));

    //optional arguments <i>
    uint32_t i = parseOptionalArgs(argc, argv); //sets i, 1 by default

    uint64_t times[i];

    for (uint32_t j = 0; j < i; j++) {
        MT_COLLATZ collatz(N, T);
        CollatzResults result = collatz.startCollatz();
        times[j] = result.time;
        Histogram* histo = result.histogram;
        if (j == i - 1) histo->print(); // Print on last (doesn't affect the results, just keeps the output less cluttered)
        delete histo;
    }

    uint64_t avgTime = 0;

    cerr << "Times: " << endl;

    for (uint32_t j = 0; j < i; j++) {
        cerr << times[j];
        if (j < i - 1) cerr << ",";
        avgTime += times[j];
    }

    cerr << endl;
    
    avgTime/=i;

    cerr << N << ", " << (int)T << ", " << "average time: " << avgTime << " ns" << endl; // Output time to std::cerr
    return 0;
}