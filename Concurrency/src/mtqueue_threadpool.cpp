#include <iostream>
#include <random>
#include <chrono>
#include <atomic>
#include <optional>
#include "thread_pool.hpp"
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

int main() {
    mtqueue<int> q;
    thread_pool pool(4);
    
    // Spawn multiple threads for producer and consumer using the thread pool
    for (int i = 0; i < 10; ++i) {
        pool.async(produce, std::ref(q));
        pool.async(consume, std::ref(q));
    }
   
    // Let the threads run for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
    done = true;
    
    // NOTE: Thread pool destructor automatically stops and joins all threads when it goes out of scope (end of main).
}