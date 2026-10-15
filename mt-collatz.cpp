/**
* mt-collatz.cpp
*
* Ayden Petersen
* Jackson Puls
* Project 2 - mt-collatz
* 
*/
#include <thread>
#include <atomic>

#include "mt-collatz.hpp"
#include "stopwatch.hpp"

#define MAX_CHUNK_SIZE 10000 // Each thread will pull at most MAX_CHUNK_SIZE from COUNTER, which will reduce the amount of thrashing that occurs in the cache when multiple threads are reading and modifying COUNTER.

MT_COLLATZ::MT_COLLATZ(uint64_t N, uint8_t T): N(N), T(T) {
    // Essentially tries to make the chunk_size evenly split N amongst the threads, unless if it's greater than MAX_CHUNK_SIZE, which it will just cap to that.
    // If N is less than T, then the chunk_size will just default to N.
    if ((N / T) <= 0) {
        chunk_size = N;
    }
    else if ((N / T) > MAX_CHUNK_SIZE) {
        chunk_size = MAX_CHUNK_SIZE;
    }
    else {
        chunk_size = N / T;
    }

    no_cache = NO_CACHE;

    // This array is used by calc_collatz_stoptime to cache previously calculated stop times, since a lot of numbers will repeat the same paths. This speeds up the program a crap ton.
    // Accesses are at i-1 since numbers 1 through N will be calculated, while the the array will go from 0 through N-1.
    if (!no_cache) collatz_cache = new uint16_t[N]{0}; 
}

MT_COLLATZ::~MT_COLLATZ() {
    if (!no_cache) delete[] collatz_cache;
    if (!no_cache) collatz_cache = nullptr;
}

uint64_t MT_COLLATZ::calcCollatzStoptime(uint64_t n) {
    uint64_t stoptime = 0;
    uint64_t i = n; // Creates a copy to work on so that the original number is still accessible.

    while (i > 1) {
        // The actual Collatz sequence.
        if (i % 2 == 0) i /= 2;
        else i = 3 * i + 1;
        stoptime++;

        if (no_cache) continue;

        // Skips checking cache if i > n since it's not likely to have anything above n, plus this prevents out of bounds reads/writes.
        if (i <= n) {
            // If there's a value cached for the current i, add it and break out of the loop.
            uint64_t cached_stoptime = collatz_cache[i-1];
            if (cached_stoptime != 0) {
                stoptime += cached_stoptime;
                break;
            }
        }
    }
    
    if (no_cache) return stoptime;
    
    // If the value at collatz_cache[n-1] is zero, then assign stoptime to it.
    if (collatz_cache[n-1] == 0) {
        collatz_cache[n-1] = stoptime;
    }

    return stoptime;
}

void MT_COLLATZ::threadWorker(uint64_t* h) {
    uint64_t local_counter; // This is used along with chunk_size to reduce simultaneous reads and writes to COUNTER by different threads.

    while (true) {
        if (COUNTER > N) return; // Check to prevent any further calculations past N.

        local_counter = COUNTER.fetch_add(chunk_size, std::memory_order_acq_rel); // Stores current COUNTER value in local_counter and increments COUNTER by chunk_size in 1 step

        // Iterates over local_counter up to local_counter + chunk_size, and breaks if the counter goes over N, then adds the stop time to the thread's local histogram.
        for (uint64_t i = local_counter; i < (local_counter + chunk_size) && i <= N; i++) {
            uint64_t stopping_time = calcCollatzStoptime(i);
            if (stopping_time <= K) h[stopping_time]++; //check if stopping time is less than K to protect memory for large N
        }
    }
}

CollatzResults MT_COLLATZ::startCollatz() {
    COUNTER = 1; // Always reset since this function could be called multiple times.
    
    std::thread threads[T]{};

    // initializer lists cannot be used on VLA's for some reason :(
    // ie. uint64_t local_histograms[T][K+1]{0};
    uint64_t* local_histograms[T]; // This is used to remove the need to synchronize accesses to the main histogram, as each thread gets its own array and no other array will compete for access. Later these are combined into the main histogram.
    //initialize a stopwatch to time the sequence
    StopWatch s;
    s.start();
    // Starts each thread and assigns them a histogram.
    for (uint8_t i = 0; i < T; i++) {
        local_histograms[i] = new uint64_t[K+1]{0};
        threads[i] = std::thread(&MT_COLLATZ::threadWorker, this, local_histograms[i]); //assign each thread with member function
    }
    Histogram* h = new Histogram();
    // Joins the threads and combines each of their histograms.
    for (uint8_t i = 0; i < T; i++) {
        threads[i].join();

        for (uint32_t j = 0; j < K+1; j++) {
            h->updateFrequency(j, local_histograms[i][j]); //add frequencies from the local histograms to the main histogram
        }
        delete[] local_histograms[i]; //Delete local histogram after merging
    }

    s.stop(); //stop timing after all work is done
    return {s.getElapsedTimeNs(), h};
}