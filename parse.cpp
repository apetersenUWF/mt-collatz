#include "parse.hpp"
#include "mt-collatz.hpp" //for NO_LOCK
using namespace std;

unsigned long long parsePositive(const string& arg, const string& name, unsigned long long maxVal) {
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
    exit(1);
}

unsigned int parseOptionalArgs(int argc, char** argv) {
    unsigned int i = 1; // number of times to run the program, default is 1
    int j = 3;

    // -nolock should be arg3
    if (argc > j && strcmp(argv[j], "-nolock") == 0) {
        NO_LOCK = true;
        j++;
    }
    // i is arg3 if -nolock was omitted, else arg4
    if (argc > j) {
        i = static_cast<unsigned int>(parsePositive(argv[j], "i", UINT_MAX));
        j++;
    }
    // anything left over: too many args, or -nolock placed after i
    if (argc > j) {
        cerr << "Invalid argument: " << argv[j] << endl;
        exit(1);
    }
    return i;
}