#ifndef SESSION2_BENCHMARK_H
#define SESSION2_BENCHMARK_H

#include <functional>
#include <chrono>
#include <iostream>
#include "timer.h"

class benchmark {
public:
    static void benchmark_function(int runs, const std::function<void (void)> &func);
};


#endif //SESSION2_BENCHMARK_H
