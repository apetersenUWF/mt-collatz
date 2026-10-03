#include "histogram.hpp"
int main(int argc, char** argv) {
    Histogram h("test1.csv", 100, 5);
    h.generateCSV();
    return 0;
}