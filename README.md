# mt-collatz Project COP4634
### By Jackson Puls and Ayden Petersen

A multithreaded application that generates a histogram in a .csv format of the stopping times of every number from 1 through N of the Collatz sequence, then outputs the time it took to run in nanoseconds. The user can choose any number of N and any number of threads, as well as enter how many times the calculation should run so the user can get a better average.

## Build
```
make clean
make
```

## Run
```
./mt-collatz <N> <T> [i] [-nocache] 
```
`N` must at least be 1, and theoretically go up to `ULLONG_MAX` (18,446,744,073,709,551,615) but the program is limited to how much RAM can be allocated to the program when `-nocache` is not provided. The amount of RAM the program needs is about equal to 2*`N` bytes. If `-nocache` is provided then RAM shouldn't be an issue.

`T` must at least be 1 and at most `UINT8_MAX` (255). Any number higher than what your system has may have no affect or negatively impact performance.

`i` is optional, it defaults to 1. This just tells the program to run `i` amount of times. Then the program will just average the times together.

The program will output the histogram to stdout and output the times on stderr, so to save to a file, you must use > or >> for the histogram and 2> or 2>> for the times in order to redirect them.