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
/*
* A function that parses a string and returns an unsigned long long within the range 1 to maxVal
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
unsigned long long parsePositive(const std::string& arg, const std::string& name, unsigned long long maxVal);

/*
* A function that parses optional arguments -nolock and i
* Upon success sets the value of NO_LOCK and returns i
*     * For success -nolock must preceed i and no trailing arguments
*     * if i was omitted, returns 1 to run the program once by default
* Upon failure prints the invalid argument to stderr and exits
*     * Fails if it encounters an argument that is not -nolock or i
*     * OR if i preceeds -nolock
* @param int argc The same as the argc from main
* @param char** argv The same argv from main
* Usage: unsigned int i = parseOptionalArgs(argc, argv);
*/
unsigned int parseOptionalArgs(int argc, char** argv);
