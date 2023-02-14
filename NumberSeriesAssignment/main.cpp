#include <iostream>
#include "NumberSeries.h"
#include "Timer.h"

int main() {
    // Fill an array/vector of 100.000 random number series, each with 100 elements.
    constexpr int series_vec_size = 100'000;
    
    std::vector<NumberSeries> series_vec(series_vec_size);

    for (int i = 0; i < series_vec_size; i++) {
        series_vec.push_back(NumberSeries::make_random(100));
    }

    // Add a random number series to each of number series in the array/vector.
    for (auto &item: series_vec) {
        auto series = NumberSeries::make_random(100);
        item += series;
    }

    // Sort the vector according to the amplitudes of number series (as given by the < operator).
    // record how much time this takes
    std::cout << "Sorting now..." << std::endl;
    
    Timer timer;
    timer.start();
    
    std::sort(series_vec.begin(), series_vec.end(), [](const NumberSeries &lhs, const NumberSeries &rhs) {
        return lhs < rhs;
    });
    
    timer.stop();
    
    std::cout << "Elapsed time for sorting the series vector: " << timer.elapsed() << "ms." << std::endl;
    
    return 0;
}
