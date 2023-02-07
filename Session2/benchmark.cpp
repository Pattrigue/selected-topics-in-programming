#include "benchmark.h"

void benchmark::benchmark_function(int runs, const std::function<void()> &func) {
    std::cout << "Benchmarking on " << runs << " runs..." << std::endl;
    
    double total = 0;

    for (int i = 0; i < runs; i++) {
        timer t;
        t.start();

        func();

        total += t.stop();
    }

    double average = total / runs;
    std::cout << "Average time over " << runs << " runs: " << average << " ms." << std::endl;
}