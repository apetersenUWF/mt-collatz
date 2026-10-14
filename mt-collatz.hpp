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

uint64_t calc_collatz_stoptime(uint64_t n);

void thread_worker(uint64_t N, uint64_t chunk_size, uint64_t* h);