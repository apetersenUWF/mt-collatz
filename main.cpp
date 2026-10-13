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
#include "stopwatch.hpp"
#include "parse.hpp"

using namespace std;

/*
*
MAIN
*
*/
int main(int argc, char** argv) {
    if (argc < 3 || argc > 5) {
        cerr << "Invalid input, please pass the form <N T -nolock i>" << endl;
        return 1;
    }
    //non-optional arguments <N, T>
    uint64_t N = parsePositive(argv[1], "N", ULLONG_MAX);
    uint8_t T = static_cast<uint8_t>(parsePositive(argv[2], "T", UINT8_MAX));

    //optional arguments <-nolock i>
    uint32_t i = parseOptionalArgs(argc, argv); //passively sets NO_LOCK as well

    uint64_t time = 0;

    for (uint32_t j = 0; j < i; j++) {
        Histogram h; //make histogram on each run so times are fair
        StopWatch s;

        s.start();
        start_collatz(N, T, &h);
        s.stop();

        time += s.getElapsedTimeNs();

        if (j == i - 1) h.print(); // Print on last (doesn't affect the results, just keeps the output less cluttered)
    }

    time/=i;
    cerr << N << "," << (int)T << "," << time << endl; // Output time to std::cerr
    return 0;
}