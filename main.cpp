#include <iostream>
#include <string>
#include <cstring>
#include <climits>
#include <cctype>

#include "mt-collatz.hpp"
#include "histogram.hpp"
#include "stopwatch.hpp"

using namespace std;

unsigned long long parsePositive(const string& arg, const string& name, unsigned long long maxVal) { //cleans up some repeated checks neatly
    try {
        if (arg.empty() || !isdigit(arg[0]))
            throw invalid_argument(name);

        size_t pos; //holds the index of the first nonconverted character from stoull
        unsigned long long value = stoull(arg, &pos); //string to unsigned long long

        if (pos != arg.size()) throw invalid_argument(name); //if pos usnt the last index of the string, must be trailing junk ex : "1000p"
        if (value == 0 || value > maxVal) throw out_of_range(name); //values of 0 arent allowed for any of our inputs so this is safe, also handles the different integer limits
        return value;
    }
    catch (const invalid_argument&) {
        cerr << "Invalid argument: " << name << " must be a positive integer" << endl;
    }
    catch (const out_of_range&) {
        cerr << "Out of range: " << name << " must be between 1 and " << maxVal << endl;
    }
    return 1;
}

unsigned long long averageNanoseconds(unsigned long long* times, unsigned int i) {
    unsigned long long avg = 0;
    for (int j = 0; j < i, j++) avg += times[j];
    return avg/i;
}


int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Too few arguments, please indicate N and T" << endl;
    }
    else if (argc > 5) {
        cerr << "Too many arguments, please pass the form <N T -nolock i>" << endl;
    }
    //non-optional arguments <N, T>
    unsigned long long N = parsePositive(argv[1], "N", ULLONG_MAX);
    unsigned int T = static_cast<unsigned int>(parsePositive(argv[2], "T", UINT_MAX));

    //optional arguments <-nolock i>
    unsigned int i = 1; //number of times to run the program, default is 1
    int j = 3;
    if (argc > j) { //-nolock should be arg3
        if (strcmp(argv[j], "-nolock") == 0) {
            NO_LOCK = true;
            j++;
        }
    }
    if (argc > j) {//i could be arg3 if nolock was omitted else i is arg4
        i = static_cast<unsigned int>(parsePositive(argv[j], "i", UINT_MAX));
        j++;
    }
    if (argc > j) {//if nolock was omitted and there is too many args OR if nolock was placed after i
        cerr << "Invalid argument: " << argv[j] << endl;
    }
    Histogram* h = new Histogram();
    unsigned long long* times = new unsigned long long[i];

    for (int j = 0; j < i; j++) {
        StopWatch s;
        s.start();
        start_collatz(N, T, h);
        s.stop();
        times[j] = s.getElapsedTimeNs();
    }

    unsigned long long ns = averageNanoseconds(times, i);

    cout << "time = " << ns << endl;

    h->print();

    delete h;
    h = nullptr;

    delete[] times;

    return 0;
}