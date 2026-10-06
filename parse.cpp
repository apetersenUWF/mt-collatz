/**
* parse.cpp
*
* Ayden Petersen
* Jackson Puls
* Project 2 - mt-collatz
*
*/

#include "parse.hpp"
#include "mt-collatz.hpp" //for NO_LOCK
using namespace std;

unsigned long long parsePositive(const string& arg, const string& name, unsigned long long maxVal) {
    try {
        if (arg.empty() || !isdigit(arg[0])) //if the argument is empty or begins with a char that is not a digit
            throw invalid_argument(name);

        size_t pos; //holds the index of the first nonconverted character from stoull
        unsigned long long value = stoull(arg, &pos); //string to unsigned long long

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

unsigned int parseOptionalArgs(int argc, char** argv) {
    unsigned int i = 1; // number of times to run the program, default is 1
    int j = 3; //indicates the position the first optional argument should be in from argv

    // -nolock should be arg3
    if (argc > j && strcmp(argv[j], "-nolock") == 0) { //if there are more arguments and the next argument is -nolock
        NO_LOCK = true; //set nolock to be true
        j++; //increment the argument index
    }
    // i is arg3 if -nolock was omitted, else arg4
    if (argc > j) { //if there are more arguments
        i = static_cast<unsigned int>(parsePositive(argv[j], "i", UINT_MAX)); //attempt to parse the next argument as i
        j++; //increment the argument index
    }
    // anything left over: too many args, or -nolock placed after i
    if (argc > j) { //if there are more arguments
        cerr << "Invalid argument: " << argv[j] << endl; //print leftover arguments to stderr
        exit(1);
    }
    return i; //return the value for i, nolock was set passively
}