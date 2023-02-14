#include <iostream>
#include <chrono>
#include "NumberSeries.h"

int main() {
    // Fill an array/vector of 100.000 random number series, each with 100 elements.
    constexpr int series_vec_size = 100'000;
    
    std::vector<series::NumberSeries> series_vec(series_vec_size);

    for (int i = 0; i < series_vec_size; i++) {
        series_vec.push_back(series::NumberSeries::make_random(100));
    }

    // Add a random number series to each of number series in the array/vector.
    for (auto &item: series_vec) {
        auto series = series::NumberSeries::make_random(100);
        item += series;
    }

    // Sort the vector according to the amplitudes of number series (as given by the < operator).
    // record how much time this takes
    std::cout << "Sorting now..." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::sort(series_vec.begin(), series_vec.end(), [](const series::NumberSeries &lhs, const series::NumberSeries &rhs) {
        return lhs < rhs;
    });

    auto stop_time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<double, std::milli>(stop_time - start_time).count();
    
    std::cout << "Elapsed time for sorting the series vector: " << elapsed << "ms." << std::endl;
    
    return 0;
}
