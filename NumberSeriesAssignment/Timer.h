#ifndef NUMBERSERIESASSIGNMENT_TIMER_H
#define NUMBERSERIESASSIGNMENT_TIMER_H


#include <chrono>

class Timer {
public:
    void start();
    void stop();
    double elapsed() const;
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_stop_time;
};


#endif
