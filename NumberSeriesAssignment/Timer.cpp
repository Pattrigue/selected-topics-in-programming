#include "Timer.h"

void Timer::start() {
    m_start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    m_stop_time = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed() const {
    auto duration = std::chrono::duration<double, std::milli>(m_stop_time - m_start_time).count();

    return duration;
}
