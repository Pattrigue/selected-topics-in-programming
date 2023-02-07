#include <random>
#include <iostream>
#include "rng.h"
#include "benchmark.h"

constexpr int count = 10'000'000;
constexpr int min = 0;
constexpr int max = 1000;

void mt_rng() {
    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);

    int* random_numbers = new int[count];

    for (int i = 0; i < count; i++) {
        int random_number = dist(mt);
        random_numbers[i] = random_number;
    }

    delete [] random_numbers;
}

void benchmark_rngs() {
    benchmark::benchmark_function(100, mt_rng);
}