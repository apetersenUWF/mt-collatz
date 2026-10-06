/**
* mt-collatz.cpp
*
* Ayden Petersen
* Jackson Puls
* Project 2 - mt-collatz
* 
*/
#include <vector>
#include <thread>
#include <iostream>

#include "mt-collatz.hpp"

int calc_collatz_stoptime(unsigned long long n) {
    int stoptime = 0;

    while (n > 1) {
        if (n % 2 == 0) n /= 2;
        else n = 3 * n + 1;
        stoptime++;
    }

    return stoptime;
}

void thread_worker(unsigned long long N, Histogram h) {
    while (true) {
        if (!NO_LOCK) mutex.lock();

        if (COUNTER > N) {
            if (!NO_LOCK) mutex.unlock();
            break;
        }

        int stoptime = calc_collatz_stoptime(COUNTER);
        COUNTER++;
 
        h->updateFrequency(stoptime);
        if (!NO_LOCK) mutex.unlock();
    }

}

void start_collatz(unsigned long long N, unsigned int T, Histogram* h) {

    std::vector<std::jthread> threads; // jthreads will join when the thread is out of scope automatically

    for (unsigned int i = 0; i < T; i++) {
        threads.emplace_back(thread_worker, N, h);
    }
}