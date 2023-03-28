#ifndef CONCURRENCY_MTQUEUE_H
#define CONCURRENCY_MTQUEUE_H

#include <queue>

template <typename T>
class mtqueue {
	std::queue<T> container; // TODO: benchmark other containers
	// TODO: add multi-threading safety (MT-safety)
public:
	void put(T&& item) {
		// TODO: implement putting the element into container
	}
	void put(const T& item) {
		// TODO: implement putting the element into container
	}
	T get(){
		// TODO: implement fetching an element from a container
	}
};

#endif	// CONCURRENCY_MTQUEUE_H
