#include <iostream>
#include <vector>
#include <memory>
#include "Base.h"
#include "Derived.h"
#include "Timer.h"

int main() {
    constexpr int size = 10'000'000;
    Timer timer;
    
    std::vector<std::unique_ptr<Base>> v(size);
    
    // fill v with 10 million Derived objects
    for (int i = 0; i < size; ++i) {
        v[i] = std::make_unique<Derived>();
    }
    
    // measure the time it takes to call increment on all elements in v
    timer.start();

    for (int i = 0; i < size; ++i) {
        v[i]->increment();
    }
    
    timer.stop();
    std::cout << "Calling increment() on " << size << " Derived smart pointers: " << timer.elapsed() << " ms." << std::endl;
    
    // measure the time it takes to call decrement on all elements in v
    timer.start();

    for (int i = 0; i < size; ++i) {
        v[i]->decrement();
    }

    timer.stop();
    std::cout << "Calling decrement() on " << size << " Derived smart pointers: " << timer.elapsed() << " ms." << std::endl;
    
    std::vector<Derived> v2(size);
    
    // measure the time it takes to call increment on all elements in v2
    timer.start();
    
    for (int i = 0; i < size; ++i) {
        v2[i].increment();
    }
    
    timer.stop();
    
    std::cout << std::endl;
    std::cout << "Calling increment() on " << size << " Derived objects: " << timer.elapsed() << " ms." << std::endl;
    
    // measure the time it takes to call decrement on all elements in v2
    timer.start();
    
    for (int i = 0; i < size; ++i) {
        v2[i].decrement();
    }
    
    timer.stop();
    std::cout << "Calling decrement() on " << size << " Derived objects: " << timer.elapsed() << " ms." << std::endl;
    
    /*
     * 1. Calling the pure virtual function increment() is faster than calling the non-virtual function decrement().
     * This is probably because the vector consists of Derived objects, so it does not have to look up the increment
     * function in the vtable, which it has to do for the decrement function.
     * 
     * 2. Calling the methods in the Derived objects is ~2x faster than calling them in the Derived smart pointers. 
     * This is probably because the smart pointers have to dereference the pointer to get to the Derived object before
     * it can call the method.
     * This extra step introduces a bit of overhead, which adds up over the course of the loop.
    */
    
    return 0;
}
