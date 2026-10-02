#include "histogram.hpp"
#include <iostream>

Histogram::Histogram(std::string& filename, int N, int T, int k) {
  this->filename = filename;
  this->N = N;
  this->T = T;
  this->k = k;
  frequencies = new int[k+1]; //Initialize as size k+1 so that frequency k is also included
  for (int i = 0; i < k + 1; i++) frequencies[i] = 0; //Initialize all frequencies to 0
}


Histogram::~Histogram() {
  delete [] frequencies;
}


void Histogram::setSeconds(const double t) {
  s = t;
}


void Histogram::setNanoseconds(const unsigned long long t) {
  ns = t;
}


void Histogram::print() const{
  for (int i = 0; i < k + 1; i++) std::cout << i << "," << frequencies[i] << std::endl;
}


void Histogram::generateCSV() const{
  //finish this
}


bool Histogram::updateFrequency(int stoppingTime) {
  if (stoppingTime < 0 || stoppingTime > k) return false; //Check array bounds
  else {
    frequencies[stoppingTime]++; //Increment the frequency
    //This could cause a race condition for multiple threads
    //Could use a histogram for each thread and a mergeHistograms() function at the end
    //Or using thread synchronization methods could solve this

    //I think he wants us to compare results of race conditions versus no race conditions so ill leave it like this for now
    return true;
  }
}
