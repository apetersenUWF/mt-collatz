/**
* parse.cpp
*
* Ayden Petersen
* Jackson Puls
* Project 2 - mt-collatz
*
*/

#include "parse.hpp"
#include "mt-collatz.hpp"
using namespace std;

uint64_t parsePositive(const string& arg, const string& name, uint64_t maxVal) {
    try {
        if (arg.empty() || !isdigit(arg[0])) //if the argument is empty or begins with a char that is not a digit
            throw invalid_argument(name);

        size_t pos; //holds the index of the first nonconverted character from stoull
        uint64_t value = stoull(arg, &pos); //string to uint64_t

        if (pos != arg.size()) throw invalid_argument(name); //if pos usnt the last index of the string, must be trailing junk ex : "1000p"
        if (value == 0 || value > maxVal) throw out_of_range(name); //values of 0 arent allowed for any of our inputs so this is safe, also handles the different integer limits
        return value; //must be a valid input, return it
    }
    catch (const invalid_argument&) {
        cerr << "Invalid argument: " << name << " must be a positive integer" << endl;
    }
    catch (const out_of_range&) {
        cerr << "Out of range: " << name << " must be between 1 and " << maxVal << endl;
    }
    exit(1);
}

uint32_t parseOptionalArgs(int argc, char** argv) {
    uint32_t i = 1; // number of times to run the program, default is 1
    int j = 3; //indicates the position the first optional argument should be in from argv

    // i should be arg3 
    if (argc > j && strcmp(argv[j], "-nocache") != 0) { //if there are more arguments
        i = static_cast<uint32_t>(parsePositive(argv[j], "i", UINT_MAX)); //attempt to parse the next argument as i
        j++; //increment the argument index
    }
    // -nocache should be arg4
    if (argc > j && strcmp(argv[j], "-nocache") == 0) { //if there are more arguments and the next argument is -nocache
        NO_CACHE = true; //set nocache to be true
        j++; //increment the argument index
    }
    // anything left over: too many args
    if (argc > j) { //if there are more arguments
        cerr << "Invalid argument: " << argv[j] << endl; //print leftover arguments to stderr
        exit(1);
    }
    return i; //return the value for i
}