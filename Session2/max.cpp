#include <iostream>

// The original from the lecture:
double max0(double a, double b) {
    return a < b ? b : a;
}

// Version with C-style call by reference parameters - pointers passed by value
double max1(double *a, double *b) {
    return *a < *b ? *b : *a;
}

// Version with call by C++ references
double max2(double &a, double &b) {
    return a < b ? b : a;
}

// Version with call by C++ const references
double max3(const double &a, const double &b) {
    return a < b ? b : a;
}

/* Version with pointers to references don't exist (does not compile):
double max4(double &*a, double &*b) {
    // ...
}*/

// Version with references to pointers 
double max5(double *&a, double *&b) {
    return *a < *b ? *b : *a;
}

// Version with const references to pointers 
double max6(const double *&a, const double *&b) {
    return *a < *b ? *b : *a;
}

void print_maxes() { 
    double a = 0.0;
    double b = 1.0;
    
    std::cout << "max0: " << max0(a, b) << std::endl;
    std::cout << "max1: " << max1(&a, &b) << std::endl;
    std::cout << "max2: " << max2(a, b) << std::endl;
    std::cout << "max3: " << max3(a, b) << std::endl;
    
    double *pa = &a;
    double *pb = &b;
    
    std::cout << "max5: " << max5(pa, pb) << std::endl;
    
    const double *kpa = &a;
    const double *kpb = &b;

    std::cout << "max6: " << max6(kpa, kpb) << std::endl << std::endl;
}