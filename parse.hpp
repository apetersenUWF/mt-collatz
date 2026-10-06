#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <climits>
#include <cctype>
#include <cstdlib>
#include <stdexcept>

unsigned long long parsePositive(const std::string& arg, const std::string& name, unsigned long long maxVal);
unsigned int parseOptionalArgs(int argc, char** argv);
