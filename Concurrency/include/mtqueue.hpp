#ifndef CONCURRENCY_MTQUEUE_H
#define CONCURRENCY_MTQUEUE_H

#include <queue>
#include <mutex>
#include <optional>

template <typename T>
class mtqueue {
	std::queue<T> container; // TODO: benchmark other containers
    std::mutex mutex;
public:
	void put(T&& item) {
        std::lock_guard<std::mutex> lock(mutex);
        container.push(std::move(item));
	}
    
	void put(const T& item) {
        std::lock_guard<std::mutex> lock(mutex);
        container.push(item);
	}
    
	std::optional<T> get() {
        std::lock_guard<std::mutex> lock(mutex);
        
        if (container.empty()) {
            return std::nullopt;
        }
        
        T item = container.front();
        container.pop();
        
        return item;
	}
};

#endif	// CONCURRENCY_MTQUEUE_H
