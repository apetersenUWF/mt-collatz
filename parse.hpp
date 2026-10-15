/**
* parse.hpp
*
* Ayden Petersen
* Jackson Puls
* Project 2 - mt-collatz
*
*/
#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <climits>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <cstdint> // I added this because it was starting to look really ugly
/*
* A function that parses a string and returns an uint64_t within the range 1 to maxVal
* Upon success returns the value
*     * Only suceeds when there is no leading characters and no trailing characters
* Upon failure prints the name and error to stderr
*     * Fails upon out of range error or when it encounters leading characters or tailing characters
* @ param string arg The argument you want to parse ex: argv[2]
* @ param name The name of the argument you are parsing, only used for error messages
* @ param maxVal The maximum alowable value for the parsed number
* Usage: To parse the first input as a number N in the range 1 - 10000
*     * int N = parsePositive(argv[1], "n", 10000);
*/
uint64_t parsePositive(const std::string& arg, const std::string& name, uint64_t maxVal);

/*
* A function that parses optional arguments i and -nocache
* Upon success returns i
*     * For success i should be arg3 and -nocache should be arg4 with no trailing arguments
*     * if i was omitted, returns 1 to run the program once by default
*     * if -nocache was omitted, the cache stays enabled by default
*     * -nocache is set passively, so it has no effect on the output of this function
* Upon failure prints the invalid argument to stderr and exits
*     * Fails if it encounters an argument that is not i
* @param int argc The same as the argc from main
* @param char** argv The same argv from main
* Usage: uint32_t i = parseOptionalArgs(argc, argv);
*/
uint32_t parseOptionalArgs(int argc, char** argv);
