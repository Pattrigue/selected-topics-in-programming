#include <iostream>
#include "timer.h"

void timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
}

double timer::stop() {
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(stop_time - start_time).count();

    return duration;
}
