#include <iostream>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <cstring>

extern void measure_work();
extern void measure_memcpy();
extern int* copy_and_sort(const int* arr, int size);
template<typename T, std::size_t N>
extern std::array<int, N> copy_and_sort(const std::array<T, N> &arr);
extern std::vector<int> copy_and_sort(std::vector<int> &vec);
extern void swap_ends_memcpy_static();
extern int* swap_ends_memcpy_dynamic(const int* arr, int size);

int main() {
    std::cout << "Exercise 1:\n";
    measure_work();
    measure_memcpy();
    
    std::cout << "\nExercise 2:\n";
    
    // Sort a C-style array
    const int size = 7;
    
    int arr[] = {5, 2, 4, 1, 8, 9, 12};
    int* sorted_arr = copy_and_sort(arr, size);

    std::cout << "The sorted C-style array:\n";
    
    for (int i = 0; i < size; i++) { 
        std::cout << sorted_arr[i] << ' ';
    }

    std::cout << '\n';
    free(sorted_arr);
    
    // Sort std:array
    std::array<int, 4> std_arr = {3, 2, 1, 0 };
    auto sorted_std_arr = copy_and_sort(std_arr);

    std::cout << "The sorted std::array:\n";
    for (int x : sorted_std_arr) {
        std::cout << x << ' ';
    }
    
    std::cout << '\n';
    
    // Sort a vector of ints
    std::vector<int> vec {34, 22, 41, 21, 42, 11, 402, 9001, 420, 69};
    std::vector<int> sorted_vec = copy_and_sort(vec);

    std::cout << "The sorted vector of ints:\n";
    for (int x : vec) {
        std::cout << x << ' ';
    }
    
    return 1;
}

// Exercise 1
void swap_ends(int arr[], int size) {
    for (int i = size / 2 - 1, j = size - 1; i >= 0; --i, --j) {
        std::swap(arr[i], arr[j]);
    }
}

void swap_ends(std::vector<int>& arr) { // overloading the same fn-name
    for (int i = arr.size()/2 - 1, j = arr.size() - 1; i >= 0; --i, --j) {
        std::swap(arr[i], arr[j]);
    }
}

constexpr int memcpy_arr_size = 10'000'000;
static int static_arr[memcpy_arr_size];

void swap_ends_memcpy_static() {
    static int buf[memcpy_arr_size];
    
    for (int i = memcpy_arr_size / 2 - 1, j = memcpy_arr_size - 1; i >= 0; --i, --j) {
        memcpy(&buf[i], &static_arr[j], sizeof(int));
    }
}

int* swap_ends_memcpy_dynamic(const int* arr, int size) {
    int* buf = new int[size];
    
    for (int i = size / 2 - 1, j = size - 1; i >= 0; --i, --j) {
        memcpy(&buf[i], &arr[j], sizeof(int));
    }
    
    return buf;
}

void measure_memcpy() {
    double total1 = 0;
    double total2 = 0;
    
    constexpr int runs = 100;
    constexpr int dynamic_arr_size = 10'000'000;

    for (int i = 0; i < runs; ++i) {
        auto t0 = std::chrono::high_resolution_clock::now();

        swap_ends_memcpy_static();

        auto t1 = std::chrono::high_resolution_clock::now();
        total1 += std::chrono::duration<double, std::milli>(t1 - t0).count();
    }
    
    std::cout << "Statically allocated array average: " << total1 / runs << "ms\n";

    for (int i = 0; i < runs; ++i) {
        auto t0 = std::chrono::high_resolution_clock::now();
        auto dynamic_arr = new int[dynamic_arr_size];
        auto swapped = swap_ends_memcpy_dynamic(dynamic_arr, dynamic_arr_size);

        delete [] swapped;

        auto t1 = std::chrono::high_resolution_clock::now();

        total2 += std::chrono::duration<double, std::milli>(t1 - t0).count();
    }

    std::cout << "Dynamically allocated array average: " << total2 / runs << "ms\n";
}

void measure_stack_allocation(const int arr_size) {
    int c_arr[arr_size];
    std::vector<int> vec(arr_size);

    for (int i = 0; i < arr_size; ++i) {
        c_arr[i] = i;
        vec[i] = i;
    }

    auto t0 = std::chrono::high_resolution_clock::now();

    swap_ends(c_arr, arr_size);

    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Stack allocated C array: " << std::chrono::duration<double, std::milli>(t1-t0).count() << "ms\n";

    auto t2 = std::chrono::high_resolution_clock::now();

    swap_ends(vec);

    auto t3 = std::chrono::high_resolution_clock::now();
    std::cout << "Stack allocated vector: " << std::chrono::duration<double, std::milli>(t3-t2).count() << "ms\n";
}

void measure_heap_allocation(const int arr_size) {
    int* c_arr = new int[arr_size];
    auto* vec = new std::vector<int>(arr_size);
    
    for (int i = 0; i < arr_size; ++i) {
        c_arr[i] = i;
        vec->push_back(i);
    }

    auto t0 = std::chrono::high_resolution_clock::now();

    swap_ends(c_arr, arr_size);

    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Heap allocated C array: " << std::chrono::duration<double, std::milli>(t1-t0).count() << "ms\n";

    auto t2 = std::chrono::high_resolution_clock::now();

    swap_ends(*vec);

    auto t3 = std::chrono::high_resolution_clock::now();
    std::cout << "Heap allocated vector: " << std::chrono::duration<double, std::milli>(t3-t2).count() << "ms\n";
    
    delete vec;
}

void measure_work() {
    measure_stack_allocation(100000); // crashes if the value is too big because the stack is not very big
    measure_heap_allocation(10000000);  // heap is larger so therefore we can allocate more memory
}

// Exercise 2
int* copy_and_sort(const int arr[], const int size) {
    int* copy = new int[size];

    for (int i = 0; i < size; ++i) {
        copy[i] = arr[i];
    }
    
    std::sort(copy, copy + size);
    
    return copy;
}

std::vector<int> copy_and_sort(std::vector<int> &vec) {
    std::vector<int> copy = vec;
    std::sort(vec.begin(), vec.end());
    
    return copy;
}

template<typename T, std::size_t N>
std::array<int, N> copy_and_sort(const std::array<T, N> &arr) {
    std::array<int, N> copy = arr;
    std::sort(copy.begin(), copy.end());
    
    return copy;
}