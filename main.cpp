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
    unsigned long long N = parsePositive(argv[1], "N", ULLONG_MAX);
    unsigned int T = static_cast<unsigned int>(parsePositive(argv[2], "T", UINT_MAX));

    //optional arguments <-nolock i>
    unsigned int i = parseOptionalArgs(argc, argv); //passively sets NO_LOCK as well

    unsigned long long time = 0;

    for (unsigned int j = 0; j < i; j++) {
        Histogram h; //make histogram on each run so times are fair
        StopWatch s;
        s.start();
        start_collatz(N, T, h);
        s.stop();
        time += s.getElapsedTimeNs();
        if (j == i - 1) h.print();
    }
    time/=i;
    cout << "average time = " << time << " ns" << endl;
    return 0;
}