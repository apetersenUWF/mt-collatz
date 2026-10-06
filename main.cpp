#include <iostream>
#include <string>
#include <cstring>

#include "mt-collatz.hpp"
#include "histogram.hpp"
#include "stopwatch.hpp"

using namespace std;

int main(int argc, char** argv) {
    // Checks if the user inputted enough args
    if (argc < 3) {
        cerr << "argc < 3: Please enter N range and T threads" << endl;
        return 1;
    }

    // Checks if N and T are negative before any processing is done
    if (argv[1][0] == '-') {
        cerr << "Invalid argument: N must be positive" << endl;
        return 1;
    }
    if (argv[2][0] == '-') {
        cerr << "Invalid argument: T must be positive" << endl;
        return 1;
    }

    // First checks bounds of argv, then checks if the -nolock flag is present
    if (argc >= 4) {
        if (strcmp(argv[3], "-nolock") == 0) NO_LOCK = true;
    }

    unsigned long long N;
    unsigned int T;

    // Checks if N and T are valid numbers
    try {
        N = stoi(argv[1]);
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid argument: N is not a number" << endl;
        return 1;
    }
    catch (const out_of_range& e) {
        cerr << "Out of range: N is outside the valid range for a unsigned long long" << endl;
        return 1;
    }

    try {
        T = stoi(argv[2]);
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid argument: T is not a number" << endl;
        return 1;
    }
    catch (const out_of_range& e) {
        cerr << "Out of range: T is outside the valid range for a unsigned int" << endl;
        return 1;
    }

    Histogram* h = new Histogram();
    StopWatch s;

    s.start();
    start_collatz(N, T, h);
    s.stop();

    h->print();

    delete h;
    h = nullptr;

    return 0;
}