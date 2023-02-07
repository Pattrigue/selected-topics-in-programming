#define EXERCISE1
#define EXERCISE2
#define EXERCISE3
#define EXERCISE4

#include <iostream>
#include "sizes_ranges.h"
#include "endianness.h"
#include "max.h"
#include "benchmark.h"

int main() {
#ifdef EXERCISE1
    std::cout << "Exercise 2.1:" << std::endl;
    print_sizes_and_ranges();
    std::cout << std::endl;
#endif
    
#ifdef EXERCISE2
    std::cout << "Exercise 2.2:" << std::endl;
    determine_endianness();
    reinterpret_float_as_unsigned_int();
    std::cout << std::endl;
#endif

#ifdef EXERCISE3
    print_maxes();
#endif

#ifdef EXERCISE4 
    benchmark::benchmark_function(100, [=]() -> void {
        // do some work...
        for (int i = 0; i < 10000; ++i) {
            auto arr = new int[i];

            for (int j = 0; j < i; j++) {
                arr[j] = i;
            }

            delete [] arr;
        }
    });
#endif
    return 0;
}