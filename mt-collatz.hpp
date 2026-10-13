/**
* mt-collatz.hpp
*
* Ayden Petersen
* Jackson Puls
* Project 2 - mt-collatz
* 
*/
#pragma once

#include "histogram.hpp"

inline bool NO_LOCK = false;

void start_collatz(uint64_t N, uint8_t T, Histogram* h);