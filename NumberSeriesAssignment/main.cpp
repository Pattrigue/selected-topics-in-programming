#include <iostream>
#include <chrono>
#include "number_series.h"
#include "series_wrapper.h"

constexpr int series_vec_size = 100'000;

void driver() {
    // Fill an array/vector of 100.000 random number series, each with 100 elements.
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
}

void driver_wrapper() {
    // Fill an array/vector of 100.000 random number series, each with 100 elements.
    std::vector<series::NumberSeriesWrapper> series_vec(series_vec_size);

    for (int i = 0; i < series_vec_size; i++) {
        series_vec.push_back(series::NumberSeriesWrapper::make_random(100));
    }

    // Add a random number series to each of number series in the array/vector.
    for (auto &item: series_vec) {
        auto series = series::NumberSeriesWrapper::make_random(100);
        item += series;
    }

    // Sort the vector according to the amplitudes of number series (as given by the < operator).
    // record how much time this takes
    std::cout << "Sorting now (wrapper)..." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    std::sort(series_vec.begin(), series_vec.end(), [](const series::NumberSeriesWrapper &lhs, const series::NumberSeriesWrapper &rhs) {
        return lhs < rhs;
    });

    auto stop_time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<double, std::milli>(stop_time - start_time).count();

    std::cout << "Elapsed time for sorting the wrapper series vector: " << elapsed << "ms." << std::endl;
}

int main() {
    // Driver method for the NumberSeries class.
    driver();
    
    // Driver method for the NumberSeriesWrapper class, demonstrating that the interface is the same.
    driver_wrapper();
    
    // Running the program shows that sorting the vector of NumberSeriesWrapper objects is slower than sorting the
    // vector of NumberSeries. This is expected since the unique pointer introduces additional overhead.
}
