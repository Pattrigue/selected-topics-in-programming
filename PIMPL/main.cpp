#include <iostream>
#include "Car.h"

int main() {
    Car car{500, 10};
    car.Accelerate(20);
    car.Brake(5);
    
    std::cout << car.GetSpeed() << std::endl;
    
    return 0;
}
