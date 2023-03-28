#include <thread>
#include <iostream>
#include <random>
#include "mtqueue.hpp"

std::atomic<bool> done = false;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> sleep_dist(0, 500);


void produce(mtqueue<int>& q) {
	// Producer routine: put random numbers into queue
    std::uniform_int_distribution<> values_dist(0, 100);
    
    while (!done) {
        int value = values_dist(gen);
        q.put(value);
        
        std::cout << "Produced " << value << "." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_dist(gen)));
    }
}

void consume(mtqueue<int>& q) {
    // Consumer routine: fetch and print values
    while (!done) {
        std::optional<int> item = q.get();
        
        if (!item.has_value()) {
            continue;
        }
        
        std::cout << "Consumed " << item.value() << "." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_dist(gen)));
    }
}

int main(){
	// Create an instance of a queue
    mtqueue<int> q;
    
	// Spawn multiple threads for producer and consumer using the queue
    std::vector<std::jthread> threads;
    
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(produce, std::ref(q));
        threads.emplace_back(consume, std::ref(q));
    }
    
    // Let the threads run for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
    done = true;
    
    // Wait for the threads to finish
    for (auto& thread : threads) {
        thread.join();
    }
    
    // NOTE: producer and consumer expect to bind to the queue by reference:
    // 1) STL uses values, therefore plain queue argument might not work: wrap the queue into std::ref instead.
    // 2) Using std::ref is not normal: it is a red-flag that we are doing something wrong.
    //    In this case we are sharing the queue between threads -- dangerous design!
    //    But in this exercise this is how we stress-test our queue in multi-threaded (MT) environment.
    // NOTE: many successful test runs do not guarantee that the queue is MT-safe.
    // You may make your producers to work longer, try running optimized builds hoping to trigger an error,
    // or enable option(TSAN "Thread Sanitizer" ON) in the CMakeLists.txt
    // (remember to regenerate the cmake build by deleting the build directories).
    // Limitations:
    //  - clang++-13 does not ship std::jthread.
    //  - thread sanitizer is supported only on Linux and MacOS.
}