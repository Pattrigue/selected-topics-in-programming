#include <vector>
#include <future>
#include <random>
#include <iostream>

std::vector<int> produce(size_t n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);
    
    std::vector<int> result(n);
    
    for (size_t i = 0; i < n; ++i) {
        result[i] = dist(gen);
    }
    
    return result;
}

int summarize(std::vector<std::future<std::vector<int>>>&& futures){
	// Compute and return the sum of elements
    int sum = 0;
    
    for (auto& future : futures) {
        auto result = future.get(); // Blocks this thread until the future is done
        sum += std::accumulate(result.begin(), result.end(), 0);
    }
    
    return sum;
}

int main() {
    constexpr int producers_count = 10;
    std::vector<std::future<std::vector<int>>> futures;

    // Spawn several producers
    for (int i = 0; i < producers_count; ++i) {
        // 1000 corresponds to the number of elements to produce (size_t n in produce)
        auto future = std::async(std::launch::async, produce, 1000); 
        futures.push_back(std::move(future));
    }

    // Collect the futures, compute and announce summary
    int sum = summarize(std::move(futures));
    std::cout << "Sum: " << sum << "." << std::endl;
}