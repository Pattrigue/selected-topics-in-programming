﻿#include <iostream>
#include "polyline.h"

int main() {
    point a { 1.0, 5.0 };
    point b { 6.9, 4.20 };
    
    polyline line;
    
    line += a;
    line += b;

    for (const auto &point: line) {
        std::cout << point.x << ", " << point.y << std::endl;
    }
    
    if (line) {
        std::cout << "The line is non-empty :)" << std::endl; 
    } else {
        std::cout << "The line is empty :(" << std::endl;
    }
    
    return 0;
}