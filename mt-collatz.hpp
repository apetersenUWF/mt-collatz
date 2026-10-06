#pragma once

#include <mutex>

#include "histogram.hpp"

inline unsigned long long COUNTER = 1;
inline bool NO_LOCK = false;
inline std::mutex mutex;

int calc_collatz_stoptime(int n);

void thread_worker(unsigned long long N, Histogram* h);

void start_collatz(unsigned long long N, unsigned int T, Histogram* h);